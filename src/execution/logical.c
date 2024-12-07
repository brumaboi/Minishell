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
	int exit_status;

	if (!node || !data)
		return ;
	execute_asts(node->left, data);
	exit_status = data->exit_status;
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
