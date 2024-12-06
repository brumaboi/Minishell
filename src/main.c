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

int process_split(char *input, char ***split_result, t_token **tokens, t_data *data)
{
    int count;

    count = 0;
    *split_result = split_input(input, &count, tokens, data);
    if (!split_result || !tokens)
    {
        free_free(input, *split_result, *tokens, NULL);
        return (0);
    }
    return (1);
}
void process_input(t_data *data)
{
    char *input;
    char **split_result;
    t_token *tokens;
    t_ast *ast;

    tokens = NULL;
    input = NULL;
    ast = NULL;
    split_result = NULL;
    input = get_input(data);
    if (!input)
        return ;
    if (!process_split(input, &split_result, &tokens, data))
        return ;
    ast = build_ast(tokens);
    if (!ast)
    {
        free_free(input, split_result, tokens, NULL);
        return ;
    }
    execute_asts(ast, data);
    free_free(input, split_result, tokens, ast);
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
    free_env_vars(data.env);
    free_env_vars(data.exp);
    cleanup_readline();
    return (0);
}
