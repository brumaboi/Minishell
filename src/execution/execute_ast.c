/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:33:57 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/11 18:29:45 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void execute_asts(t_ast *node, t_data *data)
{
    if (!node)
        return ;
    if (node->type == N_GREAT || node->type == N_LESS || node->type == N_DGREAT || node->type == N_DLESS)
        handle_redirection(node, data);
    else if (node->type == N_PIPE)
        execute_pipe(node, data);
    else if (node->type == N_COMMAND)
        execute_commands(node, data);
    else if (node->type == N_AND || node->type == N_OR)
        execute_logical(node, data);
}
