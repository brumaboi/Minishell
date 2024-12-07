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
	char *path;
	char **envpm;

	path = find_command_path(ast->cmd_args[0], data->env);
	if (!path)
	{
		printf("minishell: %s: command not found(exe_cmd)\n", ast->cmd_args[0]);
		exit(126);
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

int fork_and_execute(t_ast *ast, t_data *data)
{
	int status;
	pid_t pid;

	pid = fork();
    if (pid < 0) // Error in forking
    {
        perror("fork");
        return (-1);
    }
    else if (pid == 0)
    {
        set_signal_default(); // Restore default SIGINT handling in the child
        execute_child_command(ast, data);
        exit(126); // This line should never be reached if execve is successful
    }
	waitpid(pid, &status, 0);
	return(status);
}

void handle_exit_status(int status, t_data *data)
{
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status); // Update exit status from child exit code
	else if (WIFSIGNALED(status))
	{
		data->exit_status = 128 + WTERMSIG(status); // Set exit status for signals (e.g., 130 for Ctrl+C)
		if (WTERMSIG(status) == SIGINT)
			printf("\n"); // Print newline if the child was interrupted by SIGINT
	}
	restore_custom_signal_handler(); // Re-enable the custom SIGINT handler in the parent
}

int execute_commands(t_ast *ast, t_data *data)
{
    int status;

	status = 0;
    if (is_builtin(ast->cmd_args)) // Check if the command is a built-in
    {
        status = execute_builtin(ast, data); // Execute built-in command and get status
        data->exit_status = status;     // Update last exit status
        return (status);
    }
    set_signal_ignore(); // Ignore SIGINT in the parent process
    status = fork_and_execute(ast, data); // Fork and execute the command
	handle_exit_status(status, data); // Handle exit status from the child process
    return (data->exit_status); // Return the last exit stat
}
