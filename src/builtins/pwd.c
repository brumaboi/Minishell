/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:47:14 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/05 11:12:02 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int exe_builtin_pwd(void)
{
    char *current_wd;

    current_wd = malloc(sizeof(char) * PATH_MAX);
    if (!current_wd)
    {
        perror("exe_pwd");
        return (1);
    }
    if (getcwd(current_wd, PATH_MAX) == NULL)
    {
        perror("exe_pwd");
        free(current_wd);
        return (1);
    }
    ft_putstr_fd(current_wd, 1);
    ft_putchar_fd('\n', 1);
    free(current_wd);
    return (0);
}
