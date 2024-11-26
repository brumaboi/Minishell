/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:33:57 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/11 18:29:45 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_redirection_type(t_ast *node)
{
	if (node->type == N_LESS) // input redirection
		return (O_RDONLY);
	else if (node->type == N_GREAT) // output redirection
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (node->type == N_DGREAT) // append output redirection
		return (O_WRONLY | O_APPEND | O_CREAT);
	else if (node->type == N_DLESS) // here document
		return (-1);
	return (-1);
}

int	open_redirection_file(t_ast *node)
{
	int	fd;
	int	flag;

    if (!node || !node->file)
    {
        return (-1);
    }
	flag = get_redirection_type(node);
	if (flag == -1)
		return (-1);
	fd = open(node->file, flag, 0644);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

static int handle_here_doc(t_ast *node)
{
    int pipefd[2];
    char *line;
    char *delimiter;

    delimiter = node->file;
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    while (1)
    {
        write(STDOUT_FILENO, "heredoc> ", 9);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;
        size_t len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(pipefd[0]);
        return (-1);
    }
    close(pipefd[0]);
    return (0);
}

int	determine_redirection(t_ast *node)
{
	int	fd;

	if (!node) 
        return (-1);
	fd = open_redirection_file(node);
	if (fd == -1)
		return (-1);
	if (node->type == N_LESS) // input redirection
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
	}
	else if (node->type == N_DLESS) // here doc
    {
        if (handle_here_doc(node) == -1)
        {
            close(fd);
            return (-1);
        }
    }
    else // output redirection
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
	}
	close(fd); // close the file after duplicating it;
	return (0);
}

void	execute_asts(t_ast *node, t_data *data)
{
	if (!node)
		return ;
	if (node->type == N_AND || node->type == N_OR)
		execute_logical(node, data);
	else if (node->type == N_PIPE)
		execute_pipe(node, data);
	else if (node->type == N_COMMAND)
		execute_commands(node, data);
	else if (node->type == N_GREAT || node->type == N_LESS)
	{
		if (determine_redirection(node) == -1)
			return ;
		execute_asts(node->left, data);
	}
}
