/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_handle_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:12:27 by marvin            #+#    #+#             */
/*   Updated: 2024/12/07 01:12:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	determine_redirection(t_ast *node)
{
	int	fd;

	if (!node || !node->file)
		return (-1);
	if (node->type == N_DLESS)
	{
		if (handle_here_doc(node) == -1)
			return (-1);
	}
	else
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

void	handle_redirection(t_ast *node, t_data *data)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (determine_redirection(node) == -1)
		return ;
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
