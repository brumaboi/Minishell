/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:36:19 by marvin            #+#    #+#             */
/*   Updated: 2024/12/07 00:36:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

void parent(int *prev_fd, int fd[2])
{
    close(fd[1]);
    if (*prev_fd != -1 && *prev_fd != STDIN_FILENO)
    {
        close(*prev_fd);
    }
    *prev_fd = fd[0];
}

void handle_child(int prev_fd, int fd[2], t_ast *node, t_data *data)
{
    signal(SIGPIPE, SIG_DFL);
    set_signal_default();
    child_redirect_input(prev_fd);
    child_redirect_output(fd);
    execute_node(node, data);
}

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

void check_command_validity(t_ast *node, t_data *data)
{
    if (node->type == N_COMMAND && 
        !is_command_valid(node->cmd_args[0], data->env))
    {
        fprintf(stderr, "minishell: %s: command not found\n", node->cmd_args[0]);
        data->exit_status = 127;
    }
}
