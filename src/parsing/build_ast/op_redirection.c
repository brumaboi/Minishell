/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:34:16 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 21:34:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_ast	*create_redirection_node(t_token_type type, char *file)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	if (type == T_GREAT)
		node->type = N_GREAT;
	else if (type == T_DGREAT)
		node->type = N_DGREAT;
	else if (type == T_LESS)
		node->type = N_LESS;
	else if (type == T_DLESS)
		node->type = N_DLESS;
	node->file = ft_strdup(file);
	if (!node->file)
		return (free(node), NULL);
	node->left = NULL;
	node->right = NULL;
	node->cmd_args = NULL;
	return (node);
}

t_ast	*create_redir(t_token **current, t_ast *ast,
						t_token_type redirection_type)
{
	t_token	*token;
	char	*file;
	t_ast	*redirection_node;

	token = *current;
	if (token && token->type == T_IDENTIFIER)
	{
		file = ft_strdup(token->value);
		if (!file)
			return (NULL);
		*current = token->next;
		redirection_node = create_redirection_node(redirection_type, file);
		free(file);
		if (!redirection_node)
			return (NULL);
		if (ast)
			redirection_node->left = ast;
		return (redirection_node);
	}
	else
		return (NULL);
}

t_ast	*parse_redirection(t_token **current, t_ast *ast)
{
	t_token			*token;
	t_token_type	redirection_type;

	if (!current || !(*current))
		return (ast);
	token = *current;
	if (token->type == T_GREAT || token->type == T_DGREAT
		|| token->type == T_LESS || token->type == T_DLESS)
	{
		redirection_type = token->type;
		*current = token->next;
		return (create_redir(current, ast, redirection_type));
	}
	return (ast);
}
