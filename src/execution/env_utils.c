/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:13:59 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/30 19:37:57 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_array(char **ary)
{
	int	i;

	i = 0;
	if (!ary)
		return ;
	while (ary[i])
		free(ary[i++]);
	i++;
	free(ary);
}

int	count_env_variables(t_var *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*create_env_entry(t_var *env)
{
	char	*entry;
	size_t	len;

	if (env->value)
	{
		len = ft_strlen(env->name) + 1 + ft_strlen(env->value);
		entry = (char *)malloc(sizeof(char) * (len) + 1);
		if (!entry)
			return (NULL);
		ft_strcpy(entry, env->name);
		ft_strcat(entry, "=");
		ft_strcat(entry, env->value);
	}
	else
	{
		entry = ft_strdup(env->name);
		if (!entry)
			return (NULL);
	}
	return (entry);
}

char	**env_to_array(t_var *env)
{
	char **envp;
	char *env_entry;
	int i;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * (count_env_variables(env) + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		env_entry = create_env_entry(env);
		if (!env_entry)
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		envp[i++] = env_entry;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
