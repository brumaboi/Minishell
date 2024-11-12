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

int exe_builtin_exit(t_ast *ast)
{
    int exit_status;
    int value;

    
    value = ft_atoi(ast->cmd_args[1]);
    if(ast->cmd_args[1] && ast->cmd_args[2])
    {
        printf("exit: too many arguments\n");
        free_cmd_args(ast->cmd_args);
        exit(1);
    }
    else if(ast->cmd_args[1])
    {
        if(ft_isdigit(value))
        {
            exit_status = ft_atoi(ast->cmd_args[1]);
            free_cmd_args(ast->cmd_args);
            exit(exit_status);
        }
        else
        {
            printf("exit: %s numeric arg required\n", ast->cmd_args[1]);
            free_cmd_args(ast->cmd_args);
            exit(255);
        }
    }
    else
    {
        free_cmd_args(ast->cmd_args);
        exit(0);
    }
    return (0);
}
