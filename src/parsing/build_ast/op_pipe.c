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
    t_ast *node = malloc(sizeof(t_ast));
    if (!node)
    {
        if (ast)
            free_ast(ast);
        if (right)
            free_ast(right);
        return (NULL);
    }
    node->type = N_PIPE;
    node->left = ast;
    node->right = right;
    node->file = NULL;
    node->cmd_args = NULL;
    return (node);
}

int pipe_syntax(t_token *token, t_ast *ast)
{
    if (!token)
        return (0);
    if (!ast || (ast->type != N_COMMAND && ast->type != N_PIPE))
        return (0);
    return (1);
}

t_ast *parse_pipe(t_token **current, t_ast *ast)
{
    t_token *token;
    t_ast *right;

    token = *current;
    if (token && token->type == T_PIPE)
    {
        token = token->next;
        if (!pipe_syntax(token, ast))
            return (free_ast(ast), NULL);
        right = parse_command(&token);
        if (!right)
            return (free_ast(ast), NULL);
        if (!ast || (ast->type != N_COMMAND && ast->type != N_PIPE))
            return (free_ast(ast), free_ast(right), NULL);
        *current = token;
        return (create_pipe_node(ast, right));
    }
    return (ast);
}
