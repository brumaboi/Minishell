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

int execute_builtin_echo(t_ast *ast, t_data *data)
{
    int i;
    int flag;
    int j;

    i = 1;
    flag = 0;
    while (ast->cmd_args[i] && ft_strncmp(ast->cmd_args[i], "-n", 2) == 0)
    {
        j = 1;
        while (ast->cmd_args[i][j] == 'n')
            j++;
        if (ast->cmd_args[i][j] == '\0' && ast->cmd_args[i][j - 1] == 'n')
            break;
        flag = 1;
        i++;
    }
    while (ast->cmd_args[i])
    {
        if (strcmp(ast->cmd_args[i], "$?") == 0)
            printf("%d", data->exit_status);
        else if (ast->cmd_args[i][0])
            printf("%s", ast->cmd_args[i]);
        else if (ast->cmd_args[i + 1])
            printf(" ");
        i++;
    }
    if (flag == 0)
        printf("\n");
    return 0;
}
