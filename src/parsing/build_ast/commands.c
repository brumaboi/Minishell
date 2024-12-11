/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:16:04 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 12:16:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static t_ast	*create_cmd_node(char **cmd_args)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = N_COMMAND;
	node->cmd_args = cmd_args;
	node->file = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static int	empty_check(t_token **token)
{
	if (!(*token)->value || (*token)->value[0] == '\0')
	{
		*token = (*token)->next;
		return (1);
	}
	return (0);
}

int	parse_arguments(t_token **token, char ***cmd_args, int *args_count)
{
	size_t	new_size;
	size_t	old_size;

	*cmd_args = NULL;
	*args_count = 0;
	while (*token && (*token)->type == T_IDENTIFIER)
	{
		if (empty_check(token))
			continue ;
		new_size = sizeof(char *) * (*args_count + 2);
		old_size = sizeof(char *) * (*args_count + 1);
		*cmd_args = ft_realloc(*cmd_args, old_size, new_size);
		if (!*cmd_args)
			return (free_cmd_args(*cmd_args), 0);
		(*cmd_args)[*args_count] = ft_strdup((*token)->value);
		if (!(*cmd_args)[*args_count])
			return (free_cmd_args(*cmd_args), 0);
		(*args_count)++;
		*token = (*token)->next;
	}
	if (*args_count == 0)
		return (0);
	(*cmd_args)[*args_count] = NULL;
	return (1);
}

t_ast	*parse_command(t_token **current)
{
	t_token	*token;
	char	**cmd_args;
	int		args_count;

	token = *current;
	if (!parse_arguments(&token, &cmd_args, &args_count))
		return (NULL);
	*current = token;
	return (create_cmd_node(cmd_args));
}
