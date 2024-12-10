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

int do_split(char *input, char ***split_result, t_token **tokens, t_data *data)
{
    int count;
    int status;

    count = 0;
    status = correct_syntax(input);
    if (status == 2)
    {
        free(input);
        data->exit_status = 2;
        return (2);
    }
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
    if (do_split(input, &split_result, &tokens, data) != 1)
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

void print_start(void)
{
    printf("\033[H\033[J");
    printf("\n");
    printf("\033[91m");
    printf("██╗    ██╗███████╗ ██████╗ ██████╗ ███╗   ███╗███████╗\n");
    usleep(400002);
    printf("██║    ██║██╔════╝██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
    usleep(400002);
    printf("██║ █╗ ██║█████╗  ██║     ██║   ██║██╔████╔██║█████╗  \n");
    usleep(400002);
    printf("██║███╗██║██╔══╝  ██║     ██║   ██║██║╚██╔╝██║██╔══╝  \n");
    usleep(400002);
    printf("╚███╔███╔╝███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
    usleep(400002);
    printf(" ╚══╝╚══╝ ╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
    printf("\033[0m");
    usleep(400002);
    printf("\033[93m");
    printf("Welcome to our Minishell! Type 'exit' to quit.\n\n");
    printf("\033[0m");
}

int main(int argc, char **argv, char **env)
{
    t_data data;

    (void)argc;
    (void)argv;
    print_start();
    init_data(&data, env);
    init_signals();
    while(1)
    {
        process_input(&data);
    }
    free_env_vars(data.env);
    free_env_vars(data.exp);
    cleanup_readline();
    return (0);
}
