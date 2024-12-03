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

int get_index(t_ast *ast, int *flag)
{
    int i;
    int j;

    i = 1;
    while (ast->cmd_args[i] && ft_strncmp(ast->cmd_args[i], "-n", 2) == 0)
    {
        j = 1;
        while (ast->cmd_args[i][j] == 'n')
            j++;
        if (ast->cmd_args[i][j] == '\0')
        {
            *flag = 1;
            i++;
        }
        else
            break ;
    }
    return (i);
}

void print_echo(char *arg, t_data *data)
{
    char *expanded_arg;

    expanded_arg = NULL;
    if (strcmp(arg, "$?") == 0)
        printf("%d", data->exit_status);
    else
    {
        expanded_arg = expand_token(arg, data);
        if (expanded_arg)
        {
            printf("%s", expanded_arg);
            free(expanded_arg);
        }
        else
            printf("%s", arg);
    }
}

int execute_builtin_echo(t_ast *ast, t_data *data)
{
    int i;
    int flag;

    flag = 0;
    i = get_index(ast, &flag);
    while (ast->cmd_args[i])
    {
        print_echo(ast->cmd_args[i], data);
        if (ast->cmd_args[i + 1])
            printf(" ");
        i++;
    }
    if (flag == 0)
        printf("\n");
    return (0);
}
