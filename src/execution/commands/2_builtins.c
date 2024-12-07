/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:49:28 by marvin            #+#    #+#             */
/*   Updated: 2024/12/07 00:49:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_builtin(char **cmd_args)
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

int	execute_builtin(t_ast *ast, t_data *data)
{
	if (!ast || !ast->cmd_args || !ast->cmd_args[0])
		return (0);
	else if (ft_strcmp(ast->cmd_args[0], "echo") == 0)
		return (execute_builtin_echo(ast, data));
	else if(ft_strcmp(ast->cmd_args[0], "cd") == 0)
		return (exe_builtin_cd(ast, data));
	else if (ft_strcmp(ast->cmd_args[0], "pwd") == 0)
		return (exe_builtin_pwd());
	else if(ft_strcmp(ast->cmd_args[0], "env") == 0)
		return (exe_builtin_env(ast, data));
	else if(ft_strcmp(ast->cmd_args[0], "export") == 0)
		return (exe_builtin_export(ast, data));
	else if(ft_strcmp(ast->cmd_args[0], "unset") == 0)
		return (exe_builtin_unset(ast, data));
	else if(ft_strcmp(ast->cmd_args[0], "exit") == 0)
		return (exe_builtin_exit(ast));
	else
		return (0);
}
