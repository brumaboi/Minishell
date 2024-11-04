/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:29:33 by marvin            #+#    #+#             */
/*   Updated: 2024/10/17 16:29:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_ast  *parse_grouping(t_token **current)
{
    t_token *token;
    t_ast *group;

    group = NULL;
    token = *current;
    if(token && token->type == T_OPAR)
    {
        *current = token->next;
        group = build_ast(*current);
        if (!group)
            return (NULL); // need to see how to handle this error
        while (*current && (*current)->type != T_CPAR)
            *current = (*current)->next;
        if (*current && (*current)->type == T_CPAR)
            *current = (*current)->next;
    }
    return (group);
}

int check_syntax(t_token *tokens)
{
    t_token *current;

    current = tokens;
    if (current && (current->type == T_PIPE || current->type == T_AND || current->type == T_OR))
        return (1);
    while (current)
    {
        if(current->type == T_PIPE && (!current->next || current->next->type == T_PIPE))
            return (1);
        if(current->type == T_AND && (!current->next || current->next->type == T_AND))
            return (1);
        if(current->type == T_OR && (!current->next || current->next->type == T_OR))
            return (1);
        current = current->next;
    }
    return (0);
}

t_ast *build_ast(t_token *tokens)
{
    t_ast *ast;
    t_token *current;

    if (check_syntax(tokens) == 1)
    {
        ft_putstr_fd("syntax error\n", 2);
        return (free_tokens(tokens), NULL);
    }
    current = tokens;
    ast = parse_command(&current);
    if (!ast)
        return (free_tokens(tokens), NULL);
    while (current)
    {
        if (current->type == T_PIPE)
        {
            if (!ast)
                return (free_tokens(tokens), free_ast(ast), NULL);
            ast = parse_pipe(&current, ast);
            if (!ast)
                return (NULL);
        }
        else if (current->type == T_AND || current->type == T_OR)
        {
            ast = parse_logical(&current, ast);
            if (!ast)
                return (free_tokens(tokens), free_ast(ast), NULL);
        }
        else if (current->type == T_GREAT || current->type == T_DGREAT || current->type == T_LESS || current->type == T_DLESS)
        {
            ast = parse_redirection(&current, ast);
            if (!ast)
                return (free_tokens(tokens), free_ast(ast), NULL);
        }
        else if (current->type == T_OPAR)
        {
            ast = parse_grouping(&current);
            if (!ast)
                return (free_tokens(tokens), free_ast(ast), NULL);
        }
        else
            return (free_tokens(tokens), free_ast(ast), NULL);
    }
    return (ast);
}
