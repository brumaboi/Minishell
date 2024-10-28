/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:47:56 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 21:47:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int built_in_echo(char **args, t_data *data)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (i > 1)
            write(1, " ", 1);
        write(1, args[i], ft_strlen(args[i]));
        i++;
    }
    if (args[1] == '\n')
        write(1, "\n", 1);
}

int built_in_cd(char **args)
{

}

int built_in_pwd(char **args)
{

}

int built_in_env(char **args)
{

}

int built_in_export(char **args)
{

}