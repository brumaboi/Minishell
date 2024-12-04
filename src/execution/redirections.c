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

int open_redirection_file(t_ast *node)
{
    int fd;
    int flag;

    if (!node || !node->file)
        return (-1);
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

int redir_fd(int fd, int target_fd, const char *error_msg)
{
    if (dup2(fd, target_fd) == -1)
    {
        perror(error_msg);
        close(fd);
        return (-1);
    }
    return (0);
}

static int process_here_doc(int *pipefd, char *delimiter)
{
    char *line;

    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
        {
            perror("readline");
            return (-1);
        }
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break ;
        }
        write(pipefd[1], line, ft_strlen(line)); // Write input to the pipe
        write(pipefd[1], "\n", 1);              // Preserve newlines
        free(line);
    }
    return (0);
}

static int handle_here_doc(t_ast *node)
{
    int pipefd[2];
    char *delimiter;

    if (!node || !node->file)
        return (-1);
    delimiter = node->file;
    create_pipe(pipefd);
    if (process_here_doc(pipefd, delimiter) == -1)
    {
        close(pipefd[1]);
        return (-1);
    }
    close(pipefd[1]); // Close the write end of the pipe
    if (redir_fd(pipefd[0], STDIN_FILENO, "dup2") == -1)
        return (-1);
    close(pipefd[0]); // Close the read end of the pipe
    return (0);
}

int determine_redirection(t_ast *node)
{
    int fd;

    if (!node || !node->file)
        return (-1);
    if (node->type == N_DLESS) // Handle here-document
    {
        if (handle_here_doc(node) == -1)
            return (-1);
    }
    else // Handle regular file-based redirection
    {
        fd = open_redirection_file(node);
        if (fd == -1)
            return (-1);
        if (node->type == N_LESS)
        {
            if (redir_fd(fd, STDIN_FILENO, "dup2 input redirection") == -1)
                return (-1);
        }
        else if (node->type == N_GREAT || node->type == N_DGREAT)
            if (redir_fd(fd, STDOUT_FILENO, "dup2 output redirection") == -1)
                return (-1);
        close(fd);
    }
    return (0);
}

void handle_redirection(t_ast *node, t_data *data)
{
    int saved_stdout;
    int saved_stdin;

    saved_stdout = dup(STDOUT_FILENO);
    saved_stdin = dup(STDIN_FILENO);
    if (determine_redirection(node) == -1)
        return;
    if (node->left)
        execute_asts(node->left, data);
    if (saved_stdout != -1)
    {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
    }
    if (saved_stdin != -1)
    {
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
    }   
}

void execute_asts(t_ast *node, t_data *data)
{
    if (!node)
        return ;
    if (node->type == N_GREAT || node->type == N_LESS || node->type == N_DGREAT || node->type == N_DLESS)
        handle_redirection(node, data);
    else if (node->type == N_PIPE)
        execute_pipe(node, data);
    else if (node->type == N_COMMAND)
        execute_commands(node, data);
    else if (node->type == N_AND || node->type == N_OR)
        execute_logical(node, data);
}
