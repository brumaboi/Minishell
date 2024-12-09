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
# include "../libft/inc/get_next_line.h"

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
    int in_fd; //input file descriptor
    int out_fd; //output file descriptor
    int pipefd[2]; //pipe file descriptor
    int exit_status; //exit status of the last command
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
	T_IDENTIFIER
}	t_token_type;

typedef enum e_quote_type
{
    NO_QUOTE,
    SINGLE_QUOTE,
    DOUBLE_QUOTE
} t_quote_type;

typedef struct s_token
{
    char *value;
    t_token_type type;
    t_quote_type quote_type;
    struct s_token *next;
} t_token;


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
} t_ast_type;

typedef struct s_ast
{
    t_ast_type type;
    struct s_ast *left;
    struct s_ast *right;
    char *file;
    char **cmd_args;
} t_ast;

typedef struct s_norm_split
{
    char **result;
    t_token **lst;
    int idx;
    t_data *data;
} t_norm_split;

//free.c
void free_split(char **split_array);
void free_ast(t_ast *ast);
void free_cmd_args(char **cmd_args);
void free_tokens(t_token *tokens);
void free_env_vars(t_var *env);
//init_data.c
void init_data(t_data *data, char **env);
void env_to_list(t_var **lst, char **env);
void add_oldpwd_exp(t_var **exp);
void sort_exp(t_var **export);
void p_lstadd_back(t_var **lst, t_var *new);
t_var *p_lstnew(char *name, char *value);
//split_input.c
int token_add(char *input, int *i, t_token **lst, t_data *data);
char *copy_token(const char *start, const char *end, t_data *data);
int is_special_char(const char *str);
char *process_special_char(const char *str);
int	special_char_len(const char *str);
char **split_input(const char *str, int *count, t_token **lst, t_data *data);
int	quote_state_and_escape(const char *str, int *in_single_quote, int *in_double_quote);
size_t get_expansion_len(const char *token, t_data *data);
void fill_expanded(const char *token, char *expanded, t_data *data);
char *expand_token(const char *token, t_data *data);
char *expand_env_var(const char *input, t_data *data);
t_token *new_token(char *value, t_token_type type, t_quote_type quote_type);
int add_token_to_list(t_token **lst, t_token *new);
const char *find_token_end(const char *start);
//user_input.c
char *get_input(t_data *data);
//build_ast.c
t_ast *parse_redirection(t_token **current, t_ast *ast);
t_ast *parse_logical(t_token **current, t_ast *ast);
t_ast *parse_pipe(t_token **current, t_ast *ast);
t_ast *parse_command(t_token **current);
t_ast *build_ast(t_token *tokens);
//signal.c
void set_signal_ignore();
void set_signal_default();
void restore_custom_signal_handler();
void init_signals(void);
//execute_commands.c
int execute_commands(t_ast *ast, t_data *data);
int execute_builtin(t_ast *ast, t_data *data);
int is_builtin(char **cmd_args);
int	execute_child_command(t_ast *ast, t_data *data);
//execute_pipe.c
void create_pipe(int fd[2]);
void fork_process(pid_t *pid);
void child_redirect_output(int fd[2]);
void child_redirect_input(int prev_fd);
void wait_for_children(void);
void pipe_fork(int fd[2], pid_t *pid);
void execute_pipe(t_ast *node, t_data *data);
void handle_child(int prev_fd, int fd[2], t_ast *node, t_data *data);
void parent(int *prev_fd, int fd[2]);
void execute_node(t_ast *node, t_data *data);
int is_command_valid(char *cmd_name, t_var *env);
void check_command_validity(t_ast *node, t_data *data);
//execute_logical.c
void execute_logical(t_ast *node, t_data *data);
//find_path.c
char    *get_enviroment_val(t_var *env, const char *name);
char    *join_path(const char *dir, const char *cmd);
char    *check_command_path(char **path, char *cmd_name);
char    *find_command_path(char *cmd_name, t_var *env);
//env utils
int     count_env_variables(t_var *env);
void    free_array(char **ary);
char    *create_env_entry(t_var *env);
char    **env_to_array(t_var *env);
// redirections
int     get_redirection_type(t_ast *node);
int     open_redirection_file(t_ast *node);
int     determine_redirection(t_ast *node);
void    execute_asts(t_ast *node, t_data *data);
int redir_fd(int fd, int target_fd, const char *error_msg);
void handle_redirection(t_ast *node, t_data *data);
int handle_here_doc(t_ast *node);
// builtins
int     execute_builtin_echo(t_ast *ast, t_data *data);
int     exe_builtin_cd(t_ast *ast, t_data *data);
char    *get_target_dir(t_data *data, char **args);
int     change_dir(char *target_dir);
int     exe_builtin_pwd(void);
int     exe_builtin_env(t_ast *ast, t_data *data);
int     exe_builtin_export(t_ast *ast, t_data *data);
int     exe_builtin_unset(t_ast *ast, t_data *data);
int     exe_builtin_exit(t_ast *ast);
int is_valid_var(char *var_name);
//cd utils
int     update_variable(t_var **env, const char *value, char *name);
t_var   *find_variable(t_var *env, char *name);
int set_variable(t_var *var, const char *value);
int     add_variable(t_var *env, const char *value, char *name);

void cleanup_readline(void);
void free_free(char *input, char **split_result, t_token *tokens, t_ast *ast);

int correct_syntax(const char *input);

#endif