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

t_ast *parse_pipe(t_token **current, t_ast *ast)
{
    t_token *token;
    t_ast *right;

    token = *current;
    if (token && token->type == T_PIPE)
    {
        token = token->next;
        if (!token)
            return (free_ast(ast), NULL);
        right = parse_command(&token);  // Parse the right side of the pipe
        if (!right)
            return (free_ast(ast), NULL);
        *current = token;  // Update the current token pointer
        return (create_pipe_node(ast, right));
    }
    return (ast);
}
