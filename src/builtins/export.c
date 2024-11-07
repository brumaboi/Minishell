/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:22:48 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/07 20:01:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//lets validate the variables first
int is_valid_var(char *var_name)
{
    int i;

    i = 1;
    if(!var_name || ((!ft_isalpha(var_name[0]) &&  var_name[0] != '_')))
    {
        return 0;
    }
    while(var_name[i] && var_name[i] != '=')
    {
        if(!ft_isalnum(var_name[i]) && var_name[i] != '_')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

// //now func for printing the variables
// static void print_var_export(t_var *var)
// {
//     t_var *export_val;

//     export_val = var;    
//     while(export_val)
//     {
//         ft_putstr_fd("declare -x", 1);
//         ft_putstr_fd(export_val->name, 1);
//         if(export_val->value)
//         {
//             ft_putstr_fd("=\"", 1);
//             ft_putstr_fd(export_val->value, 1);
//             ft_putstr_fd("\"", 1);
//         }
//         ft_putstr_fd("\n", 1);
//         export_val = export_val->next;
//     }
// }

static void process_arg(char *arg, t_data *s_data)
{
    char *equal_sgn;
    char *name;
    char *value;

    name = NULL;
    value = NULL;
    equal_sgn = ft_strchr(arg, '=');
    if(equal_sgn)
    {
        name = ft_substr(arg, 0, equal_sgn - arg);
        value = ft_strdup(equal_sgn + 1);
    }
    else
    {
        name = ft_strdup(arg);
    }
    if(!is_valid_var(name))
    {
        ft_putstr_fd("export: ", 2);
        ft_putstr_fd(arg, 2);
        ft_putstr_fd(": not a valid identifier\n", 2);
        return;
    }
    else
    {
        update_variable(&s_data->exp, value, name);
        update_variable(&s_data->env, value, name);
                
    }
    free(name);
    if(value)
        free(value);
}

int exe_builtin_export(char **args, t_data *data)
{
    int i;
    
    i = 1;
    if(!args[1])
    {
        printf("export: not enougn argument provided\n");
        return (1);
    }
    while(args[i])
    {
        if(args[i])
        {
            ft_putstr_fd("export: no", 2);
        }
        process_arg(args[i], data);
        i++;
    }
    sort_exp(&data->exp);
    return 0;
}
