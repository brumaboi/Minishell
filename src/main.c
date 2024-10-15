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

void process_input(void)
{
    t_token *tokens;
//    t_ast *ast;
//    char *input;

    tokens = NULL;
//    ast = NULL;
//    input = get_input(); //prompt + user_input fct
//    if (!input)
//        return ;
    split_input(input, NULL, &tokens); //split the input into tokens
//    ast = build_ast(tokens)  //parse the tokens into an abstract syntax tree
//    execute_ast(ast);  //execute the abstract syntax tree
    //!!!!free the memory
}

int main(int argc, char **argv, char **env)
{
    t_data data;

    init_data(&data, env);  //initialize env and exp linked lists
//    init_signals(); //set up signal handlers
    while(1)
    {
        process_input();
    }
    return (0);
}
