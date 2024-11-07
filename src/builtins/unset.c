/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:56:49 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/07 20:02:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void unset_var(t_var **list, const char *name)
{
    t_var *current;
    t_var *prev;
    
    while(current)
    {
        if(strcmp(current->name, name) == 0)
        {
         if(prev)
                prev = prev->next; 
        else
        {
            *list = current->next;
        }
        free(current->name);
        free(current->value);
        free(current);    
        }
        prev = current;
        current = current->next;
    }
}

int exe_builtin_unset(char **args, t_data *data)
{
    int i;

    while(args[i])
    {
        if(!is_valid_var(args[i]))
        {
            printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
            return (1);
        }
        else
        {
            unset_var(&data->env, args[i]);//remove from env list
            unset_var(&data->exp, args[i]);//remove from exp list
        }
        i++;
    }
    return (0);
}