/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:06:15 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/30 17:20:55 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_var *find_variable(t_var *env, const char *name)//ITERATES THROUGH LINKED LIST TO FIND VARIABLE NAMED "NAME", in our case it wil be PWD and OLDPWD
{
    while(env)
    {
        if(ft_strcmp(env->name, name) == 0)
            return (env);    
        env = env->next;
    }    
    return NULL;
}

int set_variable(t_var *var, char *value) // Updates the value of existing variable
{
    char *new_val;

    if(!var)
        return 1;
    new_val = ft_strdup(value);
    if(!new_val)
        return 1;
    if(var->value)
        free(var->value);
    var->value = new_val;
    return 0;
}


int add_variable(t_var *env, const char *value, const char name)
{
    t_var *new_var;

    new_var = malloc(sizeof(t_var));
    if(!new_var)
        return 1;
    ft_lstadd_back(&env, new_var);
    return 0;
}

int update_env_var(t_var **env, const char *value, const char *name)
{
    t_var *var;

    if(!env || !name)
    var = find_variable(*env, name);
    if(var)
        return (set_variable(var, value));
    else
        return(add_variable(env, value, name));
}