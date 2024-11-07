/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:59:31 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/07 20:09:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char **cmd_args) // checks if its built in cmmnd;
{
	if (!cmd_args || !cmd_args[0])
		return (0);
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
	char **envpm; // env variablea array

	path = find_command_path(ast->cmd_args[0], data->env);
	if (!path)
	{
		printf("minishell: %s: command not found(exe_cmd)\n", ast->cmd_args[0]);
		exit(126);
	}
	envpm = env_to_array(data->env);
	// turns env variables linked list to array af string to be able to use variable in execve
	if (!envpm)
	{
		perror("env_to_array");
		free(path);
		exit(1);
	}
	execve(path, ast->cmd_args, envpm);
	perror("execve");
	free(path);
	free_array(envpm);
	exit(126);
}

int	execute_builtin(char **args, t_data *data)
{
	if (!args || !args[0])
		return (0);
	else if (ft_strcmp(args[0], "echo") == 0)
		return (execute_builtin_echo(&args[0]));
	else if(ft_strcmp(args[0], "cd") == 0)
		return (exe_builtin_cd(&args[0], data));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (exe_builtin_pwd());
	else if(ft_strcmp(args[0], "env") == 0)
		return (exe_builtin_env(&args[0], data));
	else if(ft_strcmp(args[0], "export") == 0)
		return (exe_builtin_export(args, data));
	else if(ft_strcmp(args[0], "unset") == 0)
		return (exe_builtin_unset(args, data));
	else if(ft_strcmp(args[0], "exit") == 0)
		// return (exe_builtin_exit(args, data));
		return (0);
	else
		return (0);
}

/**
 * execute_commands - Executes a command node.
 * @node: AST node representing the command.
 * @data: Pointer to shell data structure.
 *
 * Return: Exit status of the command.
 */
int	execute_commands(t_ast *ast, t_data *data)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (is_builtin(ast->cmd_args))
		return (execute_builtin(ast->cmd_args, data));
	set_signal_ignore(); // Ignore SIGINT in the parent process
	pid = fork();
	if (pid < 0) // child process
		return (-1);
	else if (pid == 0)
	{
		set_signal_default(); // Restore default SIGINT handling in the child
		execute_child_command(ast, data);
	}
	else // Parent process,
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        {
            printf("\n"); // Print a newline if the child was interrupted by SIGINT
        }
		restore_custom_signal_handler(); // Re-enable the custom SIGINT handler in the parent
	}
	return (status);
}
