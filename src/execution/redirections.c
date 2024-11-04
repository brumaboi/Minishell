/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:33:57 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/04 19:06:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_redirection_type(t_ast *node)
{
	if (node->type == N_LESS) // input redirection
		return (O_RDONLY);
	else if (node->type == N_GREAT) // output redirection
		return (O_WRONLY | O_CREAT | O_CREAT);
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

int	determine_redirection(t_ast *node)
{
	int	fd;

	fd = open_redirection_file(node);
	if (fd == -1)
		return (-1);
	if (node->type == N_LESS) // input redirection
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
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

void execute_pipe(t_ast *node, t_data *data)
{
    int fd[2];
    pid_t pid;
    int prev_fd;
    int status;

    prev_fd = data->in_fd;
    while (node && node->type == N_PIPE)
    {
        if (pipe(fd) == -1)
            exit(EXIT_FAILURE);
        pid = fork();
        if (pid < 0)
            exit(EXIT_FAILURE);
        if (pid == 0) // Child process
        {
            if (prev_fd != STDIN_FILENO)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    exit(EXIT_FAILURE);
                close(prev_fd);
            }
            if (dup2(fd[1], STDOUT_FILENO) == -1) // Redirect output to pipe
                exit(EXIT_FAILURE);
            close(fd[0]);
            close(fd[1]);
            execute_child_command(node->left, data);
            exit(EXIT_SUCCESS);
        }
        else // Parent process
        {
            close(fd[1]); // Close the write end of the pipe in the parent
            if (prev_fd != STDIN_FILENO)
                close(prev_fd); // Close the previous input descriptor
            prev_fd = fd[0]; // Update in_fd to the read end of the pipe
        }
        node = node->right; // Move to the next command
    }
    if (node)
    {
        pid = fork();
        if (pid < 0)
            exit(EXIT_FAILURE);
        if (pid == 0) // Last child process
        {
            if (prev_fd != STDIN_FILENO)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    exit(EXIT_FAILURE);
                close(prev_fd);
            }
            execute_child_command(node, data);
            exit(EXIT_SUCCESS);
        }
        if (prev_fd != STDIN_FILENO)
            close(prev_fd); // Close the last input descriptor
    }
    while (wait(&status) > 0)
        ;
}

void	execute_asts(t_ast *node, t_data *data)
{
	if (!node)
		return ;
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
	else if (node->type == N_AND || node->type == N_OR)
	{
		return ;
		// execute_logical(node, data);// TODO;
	}
}
