/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/15 21:47:56 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 21:47:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int execute_builtin_echo(t_ast *ast)
{
    int i;
    int flag;
    int j;

    i = 1;
    flag = 0;
    while (ast->cmd_args[i] && ast->cmd_args[i][0] == '-')
    {
        j = 1;
        while (ast->cmd_args[i][j] == 'n')
            j++;
        if (ast->cmd_args[i][j] == '\0' && ast->cmd_args[i][j - 1] == 'n')
            flag++;
        else
            break ;
        i++;
    }
    while (ast->cmd_args[i])
    {
        if (!(ast->cmd_args[i][0] == '$' && ast->cmd_args[i][1]))
            printf("%s", ast->cmd_args[i]);
        if (ast->cmd_args[i + 1])
            printf(" ");
        i++;
    }
    if (flag == 0)
        printf("\n");
    return 0;
}
