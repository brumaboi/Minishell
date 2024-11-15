/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:06:15 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/11 12:02:17 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// ITERATES THROUGH LINKED LIST TO FIND VARIABLE NAMED "NAME",in our case it wil be PWD and OLDPWD
t_var	*find_variable(t_var *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

// Updates the value of existing variable
int	set_variable(t_var *var, const char *value)
{
    char *new_val;

	if (!var)
		return (1);
	new_val = ft_strdup(value);
	if (!new_val)
		return (1);
	if (var->value)
		free(var->value);
	var->value = new_val;
	return (0);
}

int add_variable(t_var *env, const char *value, char *name)
{
    t_var *new_var;

    new_var = malloc(sizeof(t_var));
    if (!new_var)
        return (1);  // Handle malloc failure
    if (name)
        new_var->name = ft_strdup(name);  // Assuming ft_strdup copies the string
    else
        new_var->name = NULL;
    if (value)
        new_var->value = ft_strdup(value);  // Assuming ft_strdup copies the string
    else
        new_var->value = NULL;
    if (!new_var->name || (value && !new_var->value))
	{
        free(new_var->name);
        free(new_var->value);
        free(new_var);
        return (1);  // Indicate failure
    }
    new_var->next = NULL;
    p_lstadd_back(&env, new_var);
    return (0);  // Success
}

int	update_variable(t_var **env, const char *value, char *name)
{
	t_var	*var;

	if (!env || !name)
		return (1);
	var = find_variable(*env, name);
	if (var)
		return (set_variable(var, value));
	else
		return (add_variable(*env, value, name));
}
