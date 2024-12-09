/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:22:48 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/12 17:53:02 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//lets validate the variables first
int is_valid_var(char *var_name)
{
    int i;

    i = 1;
    if (!var_name || ((!ft_isalpha(var_name[0]) && var_name[0] != '_')))
        return (0);
    while (var_name[i] && var_name[i] != '=')
    {
        if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void handle_invalid_var(char *arg, char *name, char *value)
{
    ft_putstr_fd("export: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": not a valid identifier\n", 2);
    free(name);
    if (value)
        free(value);
}

static void get_name_value(char *arg, char **name, char **value)
{
    char *equal_sgn;

    equal_sgn = ft_strchr(arg, '=');
    if (equal_sgn)
    {
        *name = ft_substr(arg, 0, equal_sgn - arg);
        *value = ft_strdup(equal_sgn + 1);
    }
    else
    {
        *name = ft_strdup(arg);
        *value = NULL;
    }
}

static int process_arg(char *arg, t_data *s_data)
{
    char *name;
    char *value;

    name = NULL;
    value = NULL;
    get_name_value(arg, &name, &value);
    if(!is_valid_var(name))
    {
        handle_invalid_var(arg, name, value);
        return (1);
    }
    else
    {
        update_variable(&s_data->exp, value, name);
        update_variable(&s_data->env, value, name);
    }
    free(name);
    if (value)
        free(value);
    return (0);
}

int exe_builtin_export(t_ast *ast, t_data *data)
{
    int i;
    char **args;
    int flag;
    
    i = 1;
    args = ast->cmd_args;
    if(!args[1])
    {
        printf("export: not enougn argument provided\n");
        return (1);
    }
    while(args[i])
    {
        flag = process_arg(args[i], data);
        i++;
    }
    sort_exp(&data->exp);
    return (flag);
}
