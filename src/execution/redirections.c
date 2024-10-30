/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:33:57 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/30 19:38:34 by ezeper           ###   ########.fr       */
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

void	execute_asts(t_ast *node, t_data *data)
{
	if (!node)
		return ;
	else if (node->type == N_PIPE)
		// execute_pipe(node, data);
		return ;
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
