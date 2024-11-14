/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:47:16 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/12 17:19:40 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exe_builtin_env(t_ast *ast, t_data *data)
{
	char **args;
	t_var *current_env;

	args = ast->cmd_args;
	if (args[1])
	{
		printf("env: %s: no such file or directpry\n", args[1]);
		return (1);
	}
	current_env = data->env;
	data->env = data->env->next;
	while (current_env)
	{
		if (current_env->value) // to make sure NAME=VALUE format is printed
		{
			ft_putstr_fd(current_env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current_env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		current_env = current_env->next;
	}
	return (0);
}
