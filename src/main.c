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

//abstract syntax tree

char *get_input(t_data *data)
{
    char *input;

    (void)data;
    input = readline("minishell>");
    if (!input)
        return (NULL);
    if (*input)
        add_history(input);
    return (input);
}

void process_input(t_data *data)
{
    t_token *tokens;
    char *input;
//    t_ast *ast;

//    ast = NULL;
    tokens = NULL;
    input = get_input(data); //prompt + user_input fct
    if (!input)
        return ;
    split_input(input, NULL, &tokens); //split the input into tokens

    ///TODO: Build AST and execute it
    // ast = build_ast(tokens);  
    // execute_ast(ast);

    free(input);
    ///TODO: Free everything else
}

int main(int argc, char **argv, char **env)
{
    t_data data;

    (void)argc;
    (void)argv;
    init_data(&data, env);  //initialize env and exp linked lists
//    init_signals(); //set up signal handlers
    while(1)
    {
        process_input(&data);
    }
    return (0);
}
