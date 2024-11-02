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
