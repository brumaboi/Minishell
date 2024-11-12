/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:56:49 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/12 17:55:53 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void unset_var(t_var **list, const char *name)
{
    t_var *current;
    t_var *prev;
    
    current = NULL;
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

int exe_builtin_unset(t_ast *ast, t_data *data)
{
    int i;
    char **args;
    
    i = 1;
    args = ast->cmd_args;
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
