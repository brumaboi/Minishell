/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:59:31 by ezeper            #+#    #+#             */
/*   Updated: 2024/11/11 18:10:35 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	execute_child_command(t_ast *ast, t_data *data)
{
	char	*path;
	char	**envpm;

	path = find_command_path(ast->cmd_args[0], data->env);
	if (!path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", ast->cmd_args[0]);
		exit(127);
	}
	envpm = env_to_array(data->env);
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

int	fork_and_execute(t_ast *ast, t_data *data)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		set_signal_default();
		execute_child_command(ast, data);
		exit(126);
	}
	waitpid(pid, &status, 0);
	return (status);
}

void	handle_exit_status(int status, t_data *data)
{
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		data->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
	}
	restore_custom_signal_handler();
}

int	execute_commands(t_ast *ast, t_data *data)
{
	int	status;

	status = 0;
	if (is_builtin(ast->cmd_args))
	{
		status = execute_builtin(ast, data);
		data->exit_status = status;
		return (status);
	}
	set_signal_ignore();
	status = fork_and_execute(ast, data);
	handle_exit_status(status, data);
	return (data->exit_status);
}
