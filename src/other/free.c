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

void free_env_vars(t_var *env)
{
    t_var *tmp;
    while (env)
    {
        tmp = env;
        env = env->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
    }
}

void free_tokens(t_token *tokens)
{
    t_token *current;
    t_token *next;

    current = tokens;
    while (current)
    {
        next = current->next;
        if (current->value)
        {
            free(current->value);
            current->value = NULL;
        }
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
        cmd_args[i] = NULL; // Prevent dangling pointers
        i++;
    }
    free(cmd_args);
    cmd_args = NULL; // Prevent double-free
}

void free_ast(t_ast *ast)
{
    if (!ast)
        return ;
    if (ast->left)
    {
        free_ast(ast->left);
        ast->left = NULL;
    }
    if (ast->right)
    {
        free_ast(ast->right);
        ast->right = NULL;
    }
    if (ast->file)
    {
        free(ast->file);
        ast->file = NULL;
    }
    if (ast->cmd_args)
    {
        free_cmd_args(ast->cmd_args);
        ast->cmd_args = NULL; // Prevent double-free
    }
    free(ast);
    ast = NULL; // Prevent dangling pointer
}

void free_split(char **split)
{
    int i = 0;

    if (!split)
        return ;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}
