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

t_var *p_lstnew(char *name, char *value)
{
    t_var *new;

    new = (t_var *)malloc(sizeof(*new));
    if (!new)
        return (NULL);
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
            //here we take what's before the = (name) and what's after the = (value)
            //and we add the paired name and value to the linked list
            name = ft_substr(env[i], ft_strchr(env[i], '=') - env[i]);
            value = ft_strdup(ft_strchr(env[i], '=') + 1);
            p_lstadd_back(lst, p_lstnew(name, value));
        }
        i++;
    }   
}

//we add OLDPWD to the exported variables if it doesn't exist - this is used to keep track of the previous directory
void add_oldpwd_exp(t_var **exp)
{
    t_var *ptr;

    if (*exp)
    {
        ptr = *exp;
        while (ptr->next)
        {
            if (!ft_strncmp(ptr->name, "OLDPWD", 6))
                return ;
            ptr = ptr->next;
        }
        p_lstadd_back(exp, p_lstnew(ft_strdup("OLDPWD"), NULL));
    }
}

//we do this so exported vars are organized using some sort of bubblesorting
void sort_exp(t_var **export)
{
    int swapped;
    t_var *last_sorted;
    t_var *ptr;
    char *tmp_name;
	char *tmp_value;

    last_sorted = NULL;
    if (*export == NULL)
        return ;
    swapped = 1;
    while (swapped == 1)
    {
        swapped = 0;
        ptr = *export;
        while(ptr->next != last_sorted)
        {
            if (ft_strncmp(ptr->name, ptr->next->name) > 0)
            {
                tmp_name = ptr->name;
                ptr->name = ptr->next->name;
                ptr->next->name = tmp_name;
                tmp_value = ptr->value;
                ptr->value = ptr->next->value;
                ptr->next->value = tmp_value;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last_sorted = ptr;
    }
}

void init_env_exp(t_data *data, char **env)
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
void init_struct_var(t_data *data)
{
    data->env = NULL;
    data->exp = NULL;
}

void init_data(t_data *data, char **env)
{
    init_struct_var(data); //we initialize the struct
    init_env_exp(data, env); //we initialize the env and exp linked lists using the env variables
}