/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:59:07 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/24 16:36:38 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_enviroment_val(t_var *env, const char *name)
{
	while (env)
	{
		if (strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*join_path(const char *dir, const char *cmd)
{
	char	*path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	path = (char *)malloc(sizeof(char) * (dir_len + cmd_len + 2));
	if (!path)
		return (NULL);
	ft_strlcpy(path, dir, dir_len + 1);
	path[dir_len] = '/';
	ft_strlcpy(path + dir_len + 1, cmd, cmd_len + 1);
	return (path);
}

char	*check_command_path(char **path, char cmd_name)
{
	char	f_path;
	int		i;

	i = 0;
	while (path[i])
	{
		f_path = join_path(path[i], cmd_name);
		if (!f_path)
			return (NULL);
		if (access(f_path, F_OK) == 0)
			// check if file is exists and is executable
			return (f_path);
		free(f_path);
		i++;
	}
	return (NULL);
}

char	find_command_path(t_var *env, char *cmd_name)
{
	char	*path_env;
	char	**path;
	char	*res;

	if (ft_strchr(cmd_name, '/')) // if command has a '/' treat as a path
	{
		if (access(cmd_name, F_OK) == 0)
			return (ft_strdup(cmd_name));
		else
			return (NULL);
	}
	path_env = get_enviroment_val(env, "PATH");
	if (!path_env)
		return (NULL);
	path = ft_split(path_env, ':');
	if (!path)
		return (NULL);
	res = check_command_path(path, cmd_name);
	free(path);
	return (res);
}
