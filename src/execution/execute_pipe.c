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

static void execute_last_command(int prev_fd, t_ast *node, t_data *data)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid == 0)
    {
        if (prev_fd != STDIN_FILENO)
        {
            if (dup2(prev_fd, STDIN_FILENO) == -1)
                exit(EXIT_FAILURE);
            close(prev_fd);
        }
        if (is_builtin(node->cmd_args))
        {
            execute_builtin(node->cmd_args);
            exit(EXIT_SUCCESS);
        }
        else
            execute_child_command(node, data);
        exit(EXIT_SUCCESS);
    }
    if (prev_fd != STDIN_FILENO)
        close(prev_fd);
}

static void handle_child(int prev_fd, int fd[2], t_ast *node, t_data *data)
{
    if (prev_fd != STDIN_FILENO)
    {
        if (dup2(prev_fd, STDIN_FILENO) == -1)
            exit(EXIT_FAILURE);
        close(prev_fd);
    }
    if (dup2(fd[1], STDOUT_FILENO) == -1)
        exit(EXIT_FAILURE);
    close(fd[0]);
    close(fd[1]);
    if (is_builtin(node->left->cmd_args))
    {
        execute_builtin(node->left->cmd_args);
        exit(EXIT_SUCCESS);
    }
    else
        execute_child_command(node->left, data);
    exit(EXIT_SUCCESS);
}

static void handle_parent(int *prev_fd, int fd[2])
{
    close(fd[1]);
    if (*prev_fd != STDIN_FILENO)
        close(*prev_fd);
    *prev_fd = fd[0];
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
            handle_child(prev_fd, fd, node, data);
        else // Parent process
            handle_parent(&prev_fd, fd);
        node = node->right; // Move to the next command
    }
    if (node)
        execute_last_command(prev_fd, node, data);
    while (wait(&status) > 0)
        ;
    data->in_fd = dup(STDIN_FILENO);
}
