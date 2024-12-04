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

void cleanup_readline(void)
{
    clear_history();                // Clear history
    rl_free_line_state();           // Free input line state
    rl_cleanup_after_signal();      // Cleanup after signal
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
    split_result = split_input(input, &count, &tokens, data);
    if (!split_result || !tokens)
    {
        free(input);
        free_split(split_result);
        free_tokens(tokens);
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
    free_env_vars(data.env);
    free_env_vars(data.exp);
    cleanup_readline();
    return (0);
}
