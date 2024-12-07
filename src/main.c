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

int correct_syntax(const char *input)
{
    int i;
    int in_single_quote;
    int in_double_quote;
    int len;

    i = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    if (!input || *input == '\0')
        return (0); // Empty input is valid but does nothing
    while (input[i] && ft_isspace(input[i]))
        i++;
    if (is_special_char(&input[i]) > 0 && input[i] != '(') // Starts with operator
    {
        fprintf(stderr, "syntax error near unexpected token `%c`\n", input[i]);
        return (1);
    }
    while (input[i])
    {
        if (input[i] == '\'' && !in_double_quote) // Toggle single quote
            in_single_quote = !in_single_quote;
        else if (input[i] == '"' && !in_single_quote) // Toggle double quote
            in_double_quote = !in_double_quote;
        if (!in_single_quote && !in_double_quote) // Outside of quotes
        {
            len = is_special_char(&input[i]);
            if (len > 0)
            {
                if (is_special_char(&input[i + len]) > 0) // Consecutive operators
                {
                    fprintf(stderr, "syntax error near unexpected token `%c`\n", input[i + len]);
                    return (1);
                }
                i += len - 1;
            }
        }
        i++;
    }
    if (in_single_quote || in_double_quote)
    {
        fprintf(stderr, "syntax error: unmatched quote\n");
        return (1);
    }
    i--;
    while (i >= 0 && ft_isspace(input[i]))
        i--;
    if (is_special_char(&input[i]) > 0 && input[i] != ')')
    {
        fprintf(stderr, "syntax error near unexpected token `%c`\n", input[i]);
        return (1);
    }
    return (0); // Syntax is valid
}

int process_split(char *input, char ***split_result, t_token **tokens, t_data *data)
{
    int count;

    count = 0;
    *split_result = split_input(input, &count, tokens, data);
    if (!*split_result || !*tokens)
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
    if (correct_syntax(input))
    {
        free(input);
        return ; // Stop processing if there's a syntax error
    }
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
