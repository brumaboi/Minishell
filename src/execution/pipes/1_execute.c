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

#include "../../../inc/minishell.h"

int is_command_valid(char *cmd_name, t_var *env)
{
    char *command_path;

    command_path = find_command_path(cmd_name, env);
    if (command_path)
    {
        free(command_path);
        return (1);
    }
    return (0);
}

void execute_last_command(t_ast *node, t_data *data, int prev_fd)
{
    pid_t pid;

    fork_process(&pid);
    if (pid == 0)
    {
        signal(SIGPIPE, SIG_DFL);
        set_signal_default();
        child_redirect_input(prev_fd);
        if (is_builtin(node->cmd_args))
        {
            execute_builtin(node, data);
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

void execute_node(t_ast *node, t_data *data)
{
    if (node->left)
    {
        if (node->left->type == N_COMMAND)
        {
            if (!is_command_valid(node->left->cmd_args[0], data->env))
            {
                fprintf(stderr, "minishell: %s: command not found\n", node->left->cmd_args[0]);
                exit(127);
            }
            if (is_builtin(node->left->cmd_args))
            {
                execute_builtin(node->left, data);
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

void check_command_validity(t_ast *node, t_data *data)
{
    if (node->type == N_COMMAND && 
        !is_command_valid(node->cmd_args[0], data->env))
    {
        fprintf(stderr, "minishell: %s: command not found\n", node->cmd_args[0]);
        data->exit_status = 127;
    }
}

void last_last(t_ast *node, t_data *data, int prev_fd)
{
    if (node->type == N_COMMAND)
    {
        if (!is_command_valid(node->cmd_args[0], data->env))
        {
            fprintf(stderr, "minishell: %s: command not found\n", node->cmd_args[0]);
            data->exit_status = 127;
            return ;
        }
        execute_last_command(node, data, prev_fd);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

void execute_pipe(t_ast *node, t_data *data)
{
    int fd[2];
    pid_t pid;
    int prev_fd;

    prev_fd = -1;
    signal(SIGPIPE, SIG_IGN);
    set_signal_ignore();
    while (node && node->type == N_PIPE)
    {
        check_command_validity(node->left, data);
        if (data->exit_status == 127)
            return ;
        pipe_fork(fd, &pid);
        if (pid == 0)
            handle_child(prev_fd, fd, node, data);
        else
            parent(&prev_fd, fd);
        node = node->right;
    }
    if(node)
        last_last(node, data, prev_fd);
    wait_for_children();
    restore_custom_signal_handler();
    data->in_fd = dup(STDIN_FILENO);
}
