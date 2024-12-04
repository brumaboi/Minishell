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

#include "../../inc/minishell.h"

static t_var *p_lstnew(char *name, char *value)
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

//we add OLDPWD to the exported variables if it doesn't exist - this is used to keep track of the previous directory
void add_oldpwd_exp(t_var **exp)
{
    t_var *ptr;
    t_var *tmp;
    char *oldpwd;

    if (*exp)
    {
        ptr = *exp;
        while (ptr->next)
        {
            if (!ft_strncmp(ptr->name, "OLDPWD", 6))
                return ;
            ptr = ptr->next;
        }
        oldpwd = ft_strdup("OLDPWD");
        if (!oldpwd || !(tmp = p_lstnew(oldpwd, NULL)))
        {
            free_env_vars(*exp);
            *exp = NULL;
            return;
        }
        p_lstadd_back(exp, tmp);
    }
}

void swap_swap(t_var *ptr)
{
    char *tmp_name;
    char *tmp_value;

    tmp_name = ptr->name;
    ptr->name = ptr->next->name;
    ptr->next->name = tmp_name;
    tmp_value = ptr->value;
    ptr->value = ptr->next->value;
    ptr->next->value = tmp_value;
}

//we do this so exported vars are organized using some sort of bubblesorting
void sort_exp(t_var **export)
{
    int swapped;
    t_var *last_sorted;
    t_var *ptr;

    last_sorted = NULL;
    if (*export == NULL)
        return ;
    swapped = 1;
    while (swapped == 1)
    {
        swapped = 0;
        ptr = *export;
        while (ptr->next != last_sorted)
        {
            if (ptr->name && ptr->next->name
                && ft_strncmp(ptr->name, ptr->next->name, ft_strlen(ptr->name)) > 0)
            {
                swap_swap(ptr);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last_sorted = ptr;
    }
}
