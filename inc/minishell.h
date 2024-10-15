/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:22:50 by marvin            #+#    #+#             */
/*   Updated: 2024/10/08 17:22:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../libft/inc/libft.h"

typedef struct s_var
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


#endif