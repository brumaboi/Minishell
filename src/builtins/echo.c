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
    char *expanded_arg;

    i = 1;
    flag = 0;
    while (ast->cmd_args[i] && ft_strncmp(ast->cmd_args[i], "-n", 2) == 0)
    {
        j = 1;
        while (ast->cmd_args[i][j] == 'n')
            j++;
        if (ast->cmd_args[i][j] == '\0')
        {
            flag = 1;
            i++;
        }
        else
            break ;
    }
    while (ast->cmd_args[i])
    {
        expanded_arg = NULL;
        if (strcmp(ast->cmd_args[i], "$?") == 0)
            printf("%d", data->exit_status);
        else
        {
            expanded_arg = expand_token(ast->cmd_args[i], data);  // Use `expand_token` to expand variables
            if (expanded_arg)
            {
                printf("%s", expanded_arg);
                free(expanded_arg);  // Free the expanded argument after printing
            }
            else
                printf("%s", ast->cmd_args[i]);  // Print the argument as-is if no expansion is needed
        }
        if (ast->cmd_args[i + 1])
            printf(" ");
        i++;
    }
    if (flag == 0)
        printf("\n");
    return (0);
}
