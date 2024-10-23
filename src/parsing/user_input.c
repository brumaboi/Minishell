/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:26:48 by marvin            #+#    #+#             */
/*   Updated: 2024/10/17 15:26:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//function to actually get the prompt with the current working directory
char *get_prompt(void)
{
    char *prompt;
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        return (ft_strdup("minishell> "));
    }
    prompt = malloc(ft_strlen(cwd) + 3);
    if (!prompt)
        return ("minishell> ");
    ft_strcpy(prompt, cwd);
    ft_strcat(prompt, "> ");
    return (prompt);
}

//still need to implement the actual prompt
char *get_input(t_data *data)
{
    char *input;
    char *prompt;

    (void)data;
    prompt = get_prompt();
    input = readline(prompt);
    free(prompt);
    if (!input)
    {
        printf("exit\n");
        exit(0);
    }
    if (*input)
        add_history(input);
    return (input);
}
