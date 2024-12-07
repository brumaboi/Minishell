/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:08:04 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 22:08:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_var *p_lstnew(char *name, char *value)
{
    t_var *new;

    new = (t_var *)malloc(sizeof(*new));
    if (!new)
    {   
        free(name);
        free(value);
        return (NULL);
    }
    if (!name || !value)
    {
        free(new);
        return (NULL);
    }
    new->name = name;
    new->value = value;
    new->next = NULL;
    return (new);
}

void p_lstadd_back(t_var **lst, t_var *new)
{
    t_var *now;

    if (!(*lst))
        *lst = new;
    else
    {
        now = *lst;
        while (now->next)
            now = now->next;
        now->next = new;
    }
}

void env_to_list(t_var **lst, char **env)
{
    int i;
    char *name;
    char *value;

    i = 0;
    while (env[i])
    {
        if (ft_strchr(env[i], '='))
        {
            name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
            if (!name)
                return ;
            value = ft_strdup(ft_strchr(env[i], '=') + 1);
            if (!value)
            {
                free(name);
                return ;
            }
            p_lstadd_back(lst, p_lstnew(name, value));
        }
        i++;
    }   
}
