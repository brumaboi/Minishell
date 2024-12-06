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