/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:58:10 by marvin            #+#    #+#             */
/*   Updated: 2024/10/12 12:58:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	init_env_exp(t_data *data, char **env)
{
	env_to_list(&data->env, env);
	if (!data->env)
		exit(1);
	env_to_list(&data->exp, env);
	if (!data->exp)
		exit(1);
	add_oldpwd_exp(&data->exp);
	sort_exp(&data->exp);
}

static void	init_struct_var(t_data *data)
{
	data->env = NULL;
	data->exp = NULL;
	data->in_fd = dup(STDIN_FILENO);
	data->out_fd = dup(STDOUT_FILENO);
	data->pipefd[0] = 0;
	data->pipefd[1] = 0;
	data->exit_status = 0;
}

void	init_data(t_data *data, char **env)
{
	init_struct_var(data);
	init_env_exp(data, env);
}
