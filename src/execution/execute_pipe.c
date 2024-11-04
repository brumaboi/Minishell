/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:24:04 by marvin            #+#    #+#             */
/*   Updated: 2024/11/04 23:24:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
            if (is_builtin(node->left->cmd_args))
                execute_builtin(node->left->cmd_args);
            else
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
            if (is_builtin(node->cmd_args))
                execute_builtin(node->cmd_args);
            else
                execute_child_command(node, data);
            exit(EXIT_SUCCESS);
        }
        if (prev_fd != STDIN_FILENO)
            close(prev_fd); // Close the last input descriptor
    }
    while (wait(&status) > 0)
        ;
}
