/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_redir_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:12:37 by marvin            #+#    #+#             */
/*   Updated: 2024/12/07 01:12:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	get_redirection_type(t_ast *node)
{
	if (node->type == N_LESS)
		return (O_RDONLY);
	else if (node->type == N_GREAT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (node->type == N_DGREAT)
		return (O_WRONLY | O_APPEND | O_CREAT);
	else if (node->type == N_DLESS)
		return (-1);
	return (-1);
}

int	open_redirection_file(t_ast *node)
{
	int	fd;
	int	flag;

	if (!node || !node->file)
		return (-1);
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

int	redir_fd(int fd, int target_fd, const char *error_msg)
{
	if (dup2(fd, target_fd) == -1)
	{
		perror(error_msg);
		close(fd);
		return (-1);
	}
	return (0);
}
