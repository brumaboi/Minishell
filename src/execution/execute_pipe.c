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

void create_pipe(int fd[2])
{
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

void fork_process(pid_t *pid)
{
    *pid = fork();
    if (*pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void child_redirect_input(int prev_fd)
{
    if (prev_fd != -1)
    {
        if (dup2(prev_fd, STDIN_FILENO) == -1)
        {
            perror("dup2 (child, stdin)");
            exit(EXIT_FAILURE);
        }
        close(prev_fd);
    }
}

void child_redirect_output(int fd[2])
{
    if (dup2(fd[1], STDOUT_FILENO) == -1)
    {
        perror("dup2 (child, stdout)");
        exit(EXIT_FAILURE);
    }
    close(fd[0]);
    close(fd[1]);
}

void execute_node(t_ast *node, t_data *data)
{
    if (node->left)
    {
        if (node->left->type == N_COMMAND)
        {
            if (is_builtin(node->left->cmd_args))
            {
                execute_builtin(node->left->cmd_args, data);
                exit(EXIT_SUCCESS);
            }
            else
                execute_child_command(node->left, data);
        }
        else if (node->left->type == N_PIPE)
        {
            execute_pipe(node->left, data);
            exit(EXIT_SUCCESS);
        }
        else
            exit(EXIT_FAILURE);
    }
}

void parent_cleanup(int *prev_fd, int fd[2])
{
    close(fd[1]);
    if (*prev_fd != -1 && *prev_fd != STDIN_FILENO)
    {
        close(*prev_fd);
    }
    *prev_fd = fd[0];
}

void execute_last_command(t_ast *node, t_data *data, int prev_fd)
{
    pid_t pid;

    fork_process(&pid);
    if (pid == 0)
    {
        set_signal_default();
        child_redirect_input(prev_fd);
        if (is_builtin(node->cmd_args))
        {
            execute_builtin(node->cmd_args, data);
            exit(EXIT_SUCCESS);
        }
        else
        {
            execute_child_command(node, data);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        if (prev_fd != -1 && prev_fd != STDIN_FILENO)
            close(prev_fd);
    }
}

void wait_for_children()
{
    int status;

    while (wait(&status) > 0)
        ;
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        printf("\n");
    }
}

void pipe_fork(int fd[2], pid_t *pid)
{
    create_pipe(fd);
    fork_process(pid);
}

void handle_child(int prev_fd, int fd[2], t_ast *node, t_data *data)
{
    set_signal_default();
    child_redirect_input(prev_fd);
    child_redirect_output(fd);
    execute_node(node, data);
}

void execute_pipe(t_ast *node, t_data *data)
{
    int fd[2];
    pid_t pid;
    int prev_fd;

    prev_fd = -1;
    set_signal_ignore();
    while (node && node->type == N_PIPE)
    {
        pipe_fork(fd, &pid);
        if (pid == 0)
            handle_child(prev_fd, fd, node, data);
        else
            parent_cleanup(&prev_fd, fd);
        node = node->right;
    }
    if (node && node->type == N_COMMAND)
        execute_last_command(node, data, prev_fd);
    else if (node)
        exit(EXIT_FAILURE);
    wait_for_children();
    restore_custom_signal_handler();
    data->in_fd = dup(STDIN_FILENO);
}
