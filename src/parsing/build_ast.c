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

#include "../../inc/minishell.h"

t_ast *create_cmd_node(char **cmd_args)
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

t_ast *parse_operators(t_token **current, t_ast *ast)
{
    t_token *token;

    token = *current;
    while (token)
    {
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
        token = token->next;
    }
    *current = token;
    return (ast);
}

t_ast *parse_command(t_token **current)
{
    t_token *token;
    char **cmd_args;
    int args_count;

    token = *current;
    cmd_args = NULL;
    args_count = 0;
    while(token && token->type == T_IDENTIFIER)
    {
        cmd_args = ft_realloc(cmd_args, sizeof(char *) * (args_count + 2)); //we need to realloc the array because we don't know how many arguments we will have
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

t_ast *build_ast(t_token *tokens)
{
    t_ast *ast;
    t_token *current;

    current = tokens;
    ast = parse_command(&current); //function to parse input until the next operator
    if (!ast)
        return (NULL); // need to see how to handle this error
    while(current)
    {
        ast = parse_operators(&current, &ast); //function to parse the operator
        if (!ast)
            return (NULL); // need to see how to handle this error
    }
    return (ast);
}

