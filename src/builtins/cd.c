/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:20:26 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/29 18:33:09 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	update_env_values(t_var *env_lst, char *name, char value)
{
	char	*current_wd;
	char	*old_wd;

	if (getwd(current_wd) == NULL)
    {
        perror("getwd");
        return (1);
    }
    old_wd = get_enviroment_val(env_lst, "PWD");
    if(old_wd)
	{
		free(current->value);
		current->value = ft_strdup(value);
		if (!current->value)
			return (1);
		return (0);
	}
}
