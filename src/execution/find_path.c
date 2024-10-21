/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:59:07 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/21 21:27:31 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_enviroment_val(t_var *env, const char *name)
{
    while(env)
    {
        if(strcmp(env->name, name) == 0)
            return(env->value);
        env = env->next;
    }
    return NULL;  
}

char *join_path(const char *dir, const char *cmd)
{
    
}

char find_command_path(t_var *env, char *cmd_name)
{
    char *path_env;
    char *completed_path;
    int i;
    
}