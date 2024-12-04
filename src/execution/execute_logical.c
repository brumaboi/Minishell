/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:53:17 by marvin            #+#    #+#             */
/*   Updated: 2024/11/10 20:53:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void execute_logical(t_ast *node, t_data *data)
{
	int status;
	int exit_status;

	status = 0;
	if (!node || !data)
		return ;
	execute_asts(node->left, data);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (node->type == N_AND)
		{
			if (exit_status == 0)
				execute_asts(node->right, data);
		}
		else if (node->type == N_OR)
		{
			if (exit_status != 0)
				execute_asts(node->right, data);
		}
	}
}
