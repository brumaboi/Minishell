/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:24:03 by marvin            #+#    #+#             */
/*   Updated: 2024/10/08 17:24:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void execute_ast(t_ast *node, t_data *data)
// {
//     if (!node)
//         return;
//     if (node->type == N_COMMAND)
//         execute_commands(node, data); // Basic command execution (fork and execve)
//     else if (node->type == N_PIPE)
//         // TODO: execute_pipe(node->left, node->right, data); // Handle pipes between left and right nodes
//         return;
//     else if (node->type == N_GREAT || node->type == N_LESS || node->type == N_DGREAT || node->type == N_DLESS)
//         execute_redirections(node, data); // Handle redirection
//     else if (node->type == N_AND || node->type == N_OR)
//         execute_logical(node, data);  // Handle logical operators (&&, ||)
// }

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

void process_input(t_data *data)
{
    t_token *tokens;
    char *input;
    t_ast *ast;
    int  count;
    char **split_result;

    tokens = NULL;
    input = NULL;
    ast = NULL;
    split_result = NULL;
    count = 0;
    input = get_input(data);
    if (!input)
        return ;
    split_result = split_input(input, &count, &tokens);
    if (!split_result || !tokens)
    {
        free(input);
        return;
    }
    ast = build_ast(tokens);
    if (!ast)
    {
        free_tokens(tokens);
        free_split(split_result);
        free(input);
        return ;
    }
    execute_asts(ast, data);
    free_ast(ast);
    free_tokens(tokens);
    free_split(split_result);
    free(input);
}

int main(int argc, char **argv, char **env)
{
    t_data data;

    (void)argc;
    (void)argv;
    init_data(&data, env);  //initialize env and exp linked lists
    init_signals(); //set up signal handlers
    while(1)
    {
        process_input(&data);
    }
    return (0);
}
