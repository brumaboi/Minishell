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

typedef enum e_ast_type
{
    N_COMMAND,
    N_PIPE,
    N_LESS,
    N_GREAT,
    N_DLESS,
    N_DGREAT,
    N_OR,
    N_AND,
} t_ast_type;

typedef struct s_ast
{
    t_ast_type type;
    struct s_ast *left;
    struct s_ast *right;
    char *file;
    char **cmd_args;
} t_ast;

t_ast *build_ast(t_token *tokens)
{
    t_ast *ast;
    t_token *current;

    current = tokens;
    ast = parse_command(&current); //function to parse input until the next operator
    while(current)
    {
        //conditions for all op types
    }
    return (ast);
}

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
