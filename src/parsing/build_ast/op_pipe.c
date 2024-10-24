/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:32:29 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 21:32:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_ast *create_pipe_node(t_ast *ast, t_ast *right)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL); // need to see how to handle this error
    node->type = N_PIPE;
    node->left = ast;
    node->right = right;
    return (node);
}

t_ast *parse_pipe(t_token **current, t_ast *ast)
{
    t_token *token;
    t_ast *right;

    token = *current;
    if (token && token->type == T_PIPE)
    {
        token = token->next;
        right = parse_command(&token);
        if (!right)
            return (NULL); // need to see how to handle this error
        return(create_pipe_node(ast, right));
    }
    return (ast);
}
