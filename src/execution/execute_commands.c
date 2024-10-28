/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:59:31 by ezeper            #+#    #+#             */
/*   Updated: 2024/10/28 17:13:17 by ezeper           ###   ########.fr       */
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
	char **envpm;//env variablea array

	path = find_command_path(ast->cmd_args[0], data->env);
	if (!path)
	{
		printf("minishell: %s: command not found(exe_cmd)\n", ast->cmd_args[0]);
		exit(126);
	}
	envpm = env_to_array(data->env); // turns env variables linked list to array af string to be able to use variable in execve
	if (!envpm)
	{
		perror("env_to_array");
		free(path);
		exit(1);
	}
	execve(path, ast->cmd_args, envpm);
	perror("execve"); // Execute the command with the given arguments and environment variables
	free(path);
	free_array(envpm);
	exit(126);
}

int execute_builtin(char **args, t_data *data)
{
	int i;

	i = 0;
	if(!args || !args[0])
		return 0;
	else if(ft_strcmp(args[0], "echo") == 0)
		return built_in_echo(args[0], data);
	else if(ft_strcmp(args[0], "cd") == 0)
		return built_in_cd(args[0], data);
	else if(ft_strcmp(args[0], "pwd") == 0)
		return built_in_pwd(args[0], data);
	else if(ft_strcmp(args[0], "env") == 0)
		return built_in_env(args[0], data);
	else if(ft_strcmp(args[0], "export") == 0)
		return built_in_export(args, data);
	else if(ft_strcmp(args[0], "unset") == 0)
		return built_in_unset(args, data);
	else if(ft_strcmp(args[0], "exit") == 0)
		return built_in_exit(args, data);
	else
		return 0;
}

// this one deciedes whether to execute built-in command or fork a external command
int	execute_commands(t_ast *ast, t_data *data)
{ 
	int		status;
	pid_t	pid;

	status = 0;
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
	else // Parent process, waitpid() system call suspends execution of the calling process until a child specified by pid argument has changed state.
		waitpid(pid, &status, 0);
	return (status);
}
