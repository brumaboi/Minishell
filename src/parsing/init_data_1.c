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

#include "../../inc/minishell.h"

static void init_env_exp(t_data *data, char **env)
{
    env_to_list(&data->env, env); //copy/dup env variables into env list 
    if(!data->env)
        exit(1); //exit if env list is empty
    env_to_list(&data->exp, env); //copy/dup env variables into exp list
    if(!data->exp)
        exit(1); //exit if exp list is empty
    add_oldpwd_exp(&data->exp); //add OLDPWD to exp list if it doesn't exist(if directory hasn't been changed it doesn't exist)
    sort_exp(&data->exp); //sort the exp list
}

static void init_struct_var(t_data *data)
{
    data->env = NULL;
    data->exp = NULL;
}

void init_data(t_data *data, char **env)
{
    init_struct_var(data); //we initialize the struct
    init_env_exp(data, env); //we initialize the env and exp linked lists using the env variables
}