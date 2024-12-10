/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:33:02 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 21:33:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_ast *create_logical_node(t_token_type type, t_ast *ast, t_ast *right)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    if (type == T_AND)
        node->type = N_AND;
    else if (type == T_OR)
        node->type = N_OR;
    node->left = ast;
    node->right = right;
    node->file = NULL;
    node->cmd_args = NULL;
    return (node);
}

t_ast *parse_logical(t_token **current, t_ast *ast)
{
    t_token *token;
    t_ast *right;
    t_token_type type;

    token = *current;
    if (token && (token->type == T_AND || token->type == T_OR))
    {
        type = token->type;
        token = token->next;
        if (!token || token->type == T_AND || token->type == T_OR || token->type == T_PIPE)
            return (NULL);
        right = parse_command(&token);
        while (token && token->type == T_PIPE)
        {
            right = parse_pipe(&token, right);
            if (!right)
                return (NULL);
        }
        *current = token;
        return (create_logical_node(type, ast, right));
    }
    return (ast);
}
