/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:24:03 by marvin            #+#    #+#             */
/*   Updated: 2024/10/08 17:24:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//syntax tree

struct s_var
{
    char *name;
    char *value;
    struct s_var *next;
} t_var;

typedef struct s_data
{
    t_var *env; //linked list of env variables
    t_var *exp; //linked list of exp variables
} t_data;

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

void init_env_exp(t_data *data, char **env)
{
    env_to_list(&data->env, env); //copy/dup env variables into env list 
    env_to_list(&data->exp, env); //copy/dup env variables into exp list
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

int main(int argc, char **argv, char **env)
{
    t_data data;

    //init_signals
    init_data(&data, env);  //env, exp
    while(1)
    {
        //prompt
        //read_input
        //parse_input - check - tokenize - parse
        //execute
    }
}
