/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:47:16 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/05 12:29:25 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exe_builtin_env(char **args, t_data *data)
{
	// t_var *data->env

	if (args[1])
	{
		printf("env: %s: no such file or directpry\n", args[1]);
		return (1);
	}
	data->env = data->env->next;
	while (data->env)
	{
		if (data->env->value) // to make sure NAME=VALUE format is printed
		{
			ft_putstr_fd(data->env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(data->env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		data = data->env->next;
	}
	return (0);
}
