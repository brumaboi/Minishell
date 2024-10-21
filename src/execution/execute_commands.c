/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:59:31 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/21 20:36:04 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char **cmd_args) // checks if its built in cmmnd;
{
	if (strcmp(cmd_args[0], "echo") == 0)
		return (1);
	else if (strcmp(cmd_args[0], "cd") == 0)
		return (1);
	else if (strcmp(cmd_args[0], "pwd") == 0)
		return (1);
	else if (strcmp(cmd_args[0], "env") == 0)
		return (1);
	else if (strcmp(cmd_args[0], "export") == 0)
		return (1);
	else if (strcmp(cmd_args[0], "unset") == 0)
		return (1);
	else if (strcmp(cmd_args[0], "exit") == 0)
		return (1);
	return (0);
}

int	execute_child_command(t_ast *ast, t_data *data)
		// execution of external commands
{
	char *path;
	char **args;//env variablea array

	path = find_command_path(ast->cmd_args[0], data->env);
	if (!path)
	{
		printf("minishell: %s: command not found(exe_cmd)\n", ast->cmd_args[0]);
		exit(126);
	}
	args = get_args(ast->cmd_args, data->env);
	execve(path, ast->cmd_args, args);
	perror("execve");
	exit(126);
}

// this one deciedes whether to execute built-in command or fork a external command
int	execute_commands(t_ast *ast, t_data *data)
{
	int		status;
	pid_t	pid;
	char	*path;

	char **args; // env variable array
	if (is_builtin(ast->cmd_args))
		return (execute_builtin(ast->cmd_args, data));
	pid = fork();
	if (pid < 0) // child process
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		execute_child_command(ast, data);
	}
	else // Parent process
    // waitpid() system call suspends execution of the calling process until a child specified by pid argument has changed state.
		waitpid(pid, &status, 0);
	return (status);
}
