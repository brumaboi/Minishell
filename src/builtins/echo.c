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


/**
 * exe_built_in_echo - Executes the echo built-in command.
 * @args: Array of arguments passed to echo.
 *
 * Return: 0 on success.
 */
int	execute_builtin_echo(char **args)
{
	int i;
	int nl_flag;

	i = 1;
	nl_flag = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		nl_flag = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl_flag)
		printf("\n");
	return (0);
}
