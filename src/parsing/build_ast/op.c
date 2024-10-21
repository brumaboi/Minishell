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

t_ast *parse_operators(t_token **current, t_ast *ast)
{
    t_token *token;

    token = *current;
    if (token->type == T_PIPE)
        ast = parse_pipe(&token, ast);
    else if (token->type == T_AND || token->type == T_OR)
        ast = parse_logical(&token, ast);
    else if (token->type == T_GREAT || token->type == T_DGREAT || token->type == T_LESS || token->type == T_DLESS)
        ast = parse_redirection(&token, ast); //need to do
    else if (token->type == T_BACKGROUND)
        ast = parse_background(&token, ast); //need to do
    else if (token->type == T_SEMICOLON)
        ast = parse_semicolon(&token, ast); //need to do
    *current = token;
    return (ast);
}
