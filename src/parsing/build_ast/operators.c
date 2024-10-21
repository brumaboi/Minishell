/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:17:11 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 12:17:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

///TODO:
// t_ast parse_semicolon(t_token **current, t_ast *ast)
// {

// }

// t_ast parse_background(t_token **current, t_ast *ast)
// {

// }

// t_ast parse_redirection(t_token **current, t_ast *ast)
// {

// }

// t_ast *parse_logical(t_token **current, t_ast *ast)
// {

// }

t_ast create_pipe_node(t_ast *ast, t_ast right)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL); // need to see how to handle this error
    node->type = N_PIPE;
    node->left = ast;
    node->right = right;
}

t_ast parse_pipe(t_token **current, t_ast *ast)
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

t_ast *parse_operators(t_token **current, t_ast *ast)
{
    t_token *token;

    token = *current;
    if (token->type == T_PIPE)
        ast = parse_pipe(&token, ast);
    else if (token->type == T_AND || token->type == T_OR)
        ast = parse_logical(&token, ast);
    else if (token->type == T_GREAT || token->type == T_DGREAT || token->type == T_LESS || token->type == T_DLESS)
        ast = parse_redirection(&token, ast);
    else if (token->type == T_BACKGROUND)
        ast = parse_background(&token, ast);
    else if (token->type == T_SEMICOLON)
        ast = parse_semicolon(&token, ast);
    *current = token;
    return (ast);
}
