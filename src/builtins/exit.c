/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:48:02 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/11 18:33:41 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_numeric(const char *str)
{
    if (*str == '+' || *str == '-')
        str++;
    while (*str)
    {
        if (!ft_isdigit((unsigned char)*str))
            return (0);
        str++;
    }
    return (1);
}

int parse_exit_code(const char *str)
{
    long value;

    value = ft_strtol(str, NULL, 10);
    if (value < 0)
        value = 256 + (value % 256);
    return (value % 256);
}

void handle_exit(char **cmd_args)
{
    int exit_code = 0;

    if (cmd_args[1])
    {
        if (is_numeric(cmd_args[1]))
        {
            exit_code = parse_exit_code(cmd_args[1]);
            free_cmd_args(cmd_args);
            exit(exit_code);
        }
        else
        {
            printf("exit: %s numeric arg required\n", cmd_args[1]);
            free_cmd_args(cmd_args);
            exit(255);
        }
    }
    free_cmd_args(cmd_args);
    exit(0);
}

int exe_builtin_exit(t_ast *ast)
{
    if (ast->cmd_args == NULL)
        return (1);
    if (ast->cmd_args[1] && ast->cmd_args[2])
    {
        printf("exit: too many arguments\n");
        return (1);
    }
    handle_exit(ast->cmd_args);
    return (0);
}
