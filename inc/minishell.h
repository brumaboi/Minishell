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

typedef enum e_token_type
{
	T_PIPE,
	T_DGREAT,
	T_GREAT,
	T_DLESS,
	T_LESS,
	T_OR,
	T_AND,
    T_BACKGROUND,
	T_OPAR,
	T_CPAR,
    T_SEMICOLON,
	T_IDENTIFIER
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_ast_type
{
    N_COMMAND,
    N_PIPE,
    N_LESS,
    N_GREAT,
    N_DLESS,
    N_DGREAT,
    N_OR,
    N_AND,
    N_BACKGROUND,
    N_SEMICOLON
} t_ast_type;

typedef struct s_ast
{
    t_ast_type type;
    struct s_ast *left;
    struct s_ast *right;
    char *file;
    char **cmd_args;
} t_ast;

//init_data.c
void init_data(t_data *data, char **env);
void env_to_list(t_var **lst, char **env);
void add_oldpwd_exp(t_var **exp);
void sort_exp(t_var **export);
//split_input.c
int token_add(char *inpu, int i, t_token **lst);
char	*copy_token(const char *start, const char *end);
int is_special_char(const char *str);
char *process_special_char(const char *str);
int	special_char_len(const char *str);
char **split_input(const char *str, int *count, t_token **lst);
int	quote_state_and_escape(const char *str, int *in_single_quote, int *in_double_quote);
//user_input.c
char *get_input(t_data *data);
//build_ast.c
t_ast *build_ast(t_token *tokens);


#endif