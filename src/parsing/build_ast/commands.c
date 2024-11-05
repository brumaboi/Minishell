/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:16:04 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 12:16:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static t_ast *create_cmd_node(char **cmd_args)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = N_COMMAND;
    node->cmd_args = cmd_args;
    node->file = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

t_ast *parse_command(t_token **current)
{
    t_token *token;
    char **cmd_args;
    int args_count;

    token = *current;
    cmd_args = NULL;
    args_count = 0;
    while (token && token->type == T_IDENTIFIER)
    {
        if (!token->value || token->value[0] == '\0')
        {
            token = token->next;
            continue ;
        }
        cmd_args = ft_realloc(cmd_args, sizeof(char *) * (args_count + 1), sizeof(char *) * (args_count + 2)); 
        if (!cmd_args)
            return (free_cmd_args(cmd_args), NULL);
        cmd_args[args_count] = ft_strdup(token->value);
        if (!cmd_args[args_count])
            return (free_cmd_args(cmd_args), NULL);
        args_count++;
        token = token->next;
    }
    if (args_count == 0)
        return (NULL);
    cmd_args[args_count] = NULL;
    *current = token;
    return (create_cmd_node(cmd_args));
}
