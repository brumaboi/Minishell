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
    ast = build_ast(tokens);  

    ///TODO: Execute AST
    // execute_ast(ast);

    free(input);
}

int main(int argc, char **argv, char **env)
{
    t_data data;

    (void)argc;
    (void)argv;
    init_data(&data, env);  //initialize env and exp linked lists

    ///TODO: Signals
    // init_signals(); //set up signal handlers

    while(1)
    {
        process_input(&data);
    }
    return (0);
}
