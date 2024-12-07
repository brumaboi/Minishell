/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:05:37 by marvin            #+#    #+#             */
/*   Updated: 2024/11/07 23:05:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

void pipe_fork(int fd[2], pid_t *pid)
{
    create_pipe(fd);
    fork_process(pid);
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
