/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:05:45 by marvin            #+#    #+#             */
/*   Updated: 2024/11/02 13:05:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void free_tokens(t_token *tokens)
{
    t_token *current;
    t_token *next;

    current = tokens;
    while (current)
    {
        next = current->next;
        if (current->value)
            free(current->value);
        free(current);
        current = next;
    }
}

void free_cmd_args(char **cmd_args)
{
    int i = 0;

    if (!cmd_args)
        return;
    while (cmd_args[i])
    {
        free(cmd_args[i]);
        i++;
    }
    free(cmd_args);
}

void free_ast(t_ast *ast)
{
    if (!ast)
        return;

    if (ast->left)
        free_ast(ast->left);
    if (ast->right)
        free_ast(ast->right);
    if (ast->file)
        free(ast->file);
    if (ast->cmd_args)
        free_cmd_args(ast->cmd_args);

    free(ast);
}

void free_split(char **split_array)
{
    int i = 0;

    if (!split_array)
        return;
    while (split_array[i])
    {
        free(split_array[i]);
        i++;
    }
    free(split_array);
}
