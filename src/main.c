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

    ast = NULL;
    tokens = NULL;
    input = get_input(data); //get user input !!!!not done properly
    if (!input)
        return ;
    split_input(input, NULL, &tokens); //split the input into tokens
    ast = build_ast(tokens); //build the ast
    execute_asts(ast, data); //execute the ast
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
