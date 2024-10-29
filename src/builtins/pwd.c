/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:47:14 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/29 18:09:55 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int execute_builtin_pwd(void)
{
    char *current_wd;
    size_t size;
    
    size = 1;
    current_wd = malloc(sizeof(char) * size);
    if(!current_wd)
    {
        perror("exe_pwd");
        return 1;
    }
    while(getcwd(current_wd, PATH_MAX) == NULL)
    {
        size ++;
        free(current_wd);
        current_wd = malloc(sizeof(char) * size);
        if(!current_wd)
        {
            perror("exe_pwd");
            return 1;
        }
        
    }
    ft_putstr_fd(current_wd, 1);
    free(current_wd);
    ft_putchar_fd('\n', 1);
    return 0;
}
