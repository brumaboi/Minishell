/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:20:26 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/30 15:59:52 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	update_env_values(t_var *env_lst, char *name, char value)// since cd changes the state of shell env. variables must be updated so this function updates PWD and OLDPWD variables
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
		// TODO add a function to updates env values
	}
}

int get_target_dir(t_data *data, char **args)
{
	if(!args)
		return (get_enviroment_val(data->env, "HOME"));
	else if(ft_strcmp(args[1], "-") == 0)
		return(get_enviroment_val(data->env, "OLDPWD"));
	else
		return(args[1]);
}

int change_dir(t_data *data, char *target_dir)
{
	if(chdir(target_dir) == -1)
	{
		perror("cd");
		return (1);
	}
}

int exe_cd(t_data *data char **args)
{
	//TODO after finished env_value_update function built main func of cd 
}