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
        return (NULL); // need to see how to handle this error
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
    size_t old_size;

    token = *current;
    cmd_args = NULL;
    args_count = 0;
    old_size = 0;
    while(token && token->type == T_IDENTIFIER)
    {
        old_size = sizeof(char *) * (args_count + 1);
        cmd_args = ft_realloc(cmd_args, old_size, sizeof(char *) * (args_count + 2)); //we need to realloc the array because we don't know how many arguments we will have
        if (!cmd_args)
            return (NULL); // need to see how to handle this error
        cmd_args[args_count] = ft_strdup(token->value); //we copy the value of the token in the array
        if (!cmd_args[args_count])
            return (NULL); // need to see how to handle this error
        args_count++;
        token = token->next;
    }
    cmd_args[args_count] = NULL; //we need to set the last element of the array to NULL
    *current = token; //so it points to the last token processed
    return (create_cmd_node(cmd_args));
}
