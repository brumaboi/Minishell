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

void handle_exit(char **cmd_args)
{
    int value;

    if (cmd_args[1])
    {
        value = ft_atoi(cmd_args[1]);
        if (ft_isdigit(value))
        {
            exit(value);
        }
        else
        {
            printf("exit: %s numeric arg required\n", cmd_args[1]);
            free_cmd_args(cmd_args);
            exit(255);
        }
    }
    else
    {
        free_cmd_args(cmd_args);
        exit(0);
    }
}

int exe_builtin_exit(t_ast *ast)
{
    if (ast->cmd_args == NULL)
        return (1);
    if (ast->cmd_args[1] && ast->cmd_args[2])
    {
        printf("exit: too many arguments\n");
        free_cmd_args(ast->cmd_args);
        exit(1);
    }
    handle_exit(ast->cmd_args);
    return (0);
}
