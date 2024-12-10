/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:20:26 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/12 17:04:29 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	update_env_values(t_data *data)
{
	char	current_wd[PATH_MAX];
	char	*old_wd;

	if (getcwd(current_wd, sizeof(current_wd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	old_wd = get_enviroment_val(data->env, "PWD");
	if (old_wd)
		return (0);
	else
		return (1);
	if (update_variable(&data->env, current_wd, "PWD"))
		return (1);
	return (0);
}

char	*get_target_dir(t_data *data, char **args)
{
	char	*target_dir;

	if (!args[1])
	{
		target_dir = get_enviroment_val(data->env, "HOME");
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target_dir = get_enviroment_val(data->env, "OLDPWD");
	}
	else
		target_dir = args[1];
	return (target_dir);
}

int	change_dir(char *target_dir)
{
	if (chdir(target_dir) != 0)
	{
		perror("cd-chdir");
		return (1);
	}
	return (0);
}

int	check_variables_cd(char **args, t_data *data)
{
	char	*target_dir;

	if (args[2] && args[1])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	target_dir = get_target_dir(data, args);
	if (!target_dir)
	{
		if (ft_strcmp(args[1], "-") == 0)
			ft_putstr_fd("cd: OLDPWD is not set\n", 2);
		else
			ft_putstr_fd("cd: HOME is not set\n", 2);
		return (1);
	}
	return (0);
}

int	exe_builtin_cd(t_ast *ast, t_data *data)
{
	char	*target_dir;
	char	*pwd;
	char	**args;

	args = ast->cmd_args;
	if (check_variables_cd(args, data) != 0)
		return (1);
	target_dir = get_target_dir(data, args);
	if (change_dir(target_dir) != 0)
		return (1);
	if (update_env_values(data) != 0)
		return (1);
	if (ft_strcmp(args[1], "-") == 0)
	{
		pwd = get_enviroment_val(data->env, "PWD");
		if (pwd)
			ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
