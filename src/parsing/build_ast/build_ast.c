/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:29:33 by marvin            #+#    #+#             */
/*   Updated: 2024/10/17 16:29:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	check_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current && (current->type == T_PIPE
			|| current->type == T_AND || current->type == T_OR))
		return (1);
	while (current)
	{
		if (current->type == T_PIPE && (!current->next
				|| current->next->type == T_PIPE))
			return (1);
		if (current->type == T_AND && (!current->next
				|| current->next->type == T_AND))
			return (1);
		if (current->type == T_OR && (!current->next
				|| current->next->type == T_OR))
			return (1);
		current = current->next;
	}
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (check_syntax(tokens))
		return (1);
	return (0);
}

t_ast	*build_ast(t_token *tokens)
{
	t_ast	*ast;
	t_token	*current;

	if (validate_syntax(tokens) == 1)
		return (NULL);
	current = tokens;
	ast = parse_command(&current);
	if (!ast)
		return (NULL);
	while (current)
	{
		if (current->type == T_PIPE)
			ast = parse_pipe(&current, ast);
		else if (current->type == T_AND || current->type == T_OR)
			ast = parse_logical(&current, ast);
		else if (current->type == T_GREAT || current->type == T_DGREAT
			|| current->type == T_LESS || current->type == T_DLESS)
			ast = parse_redirection(&current, ast);
		else
			break ;
		if (!ast)
			return (NULL);
	}
	return (ast);
}
