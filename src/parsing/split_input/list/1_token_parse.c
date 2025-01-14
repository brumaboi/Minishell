/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:56:36 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 21:56:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

t_quote_type	detect_quote_type(const char *input, int start, int end)
{
	if (input[start] == '\'' && input[end - 1] == '\'')
		return (SINGLE_QUOTE);
	if (input[start] == '"' && input[end - 1] == '"')
		return (DOUBLE_QUOTE);
	return (NO_QUOTE);
}

int	add_identifier(char *input, int *i, t_token **lst, t_data *data)
{
	char			*value;
	char			*expanded_value;
	int				start_length[2];
	t_quote_type	quote_type;
	t_token			*new_tok;

	start_length[1] = get_length(input, i, &start_length[0]);
	quote_type = detect_quote_type(input, start_length[0] - 1, *i);
	value = ft_substr(input, start_length[0], start_length[1]);
	if (!value)
		return (1);
	if (quote_type != SINGLE_QUOTE)
	{
		expanded_value = expand_token(value, data);
		free(value);
		if (!expanded_value)
			return (1);
		value = expanded_value;
	}
	new_tok = new_token(value, T_IDENTIFIER, quote_type);
	if (!new_tok)
		return (free(value), 1);
	return (add_token_to_list(lst, new_tok));
}

int	double_special(char *input, int *i, t_token **lst, int len)
{
	t_token_type	type;
	t_token			*new_tok;
	char			*value;

	if (strncmp(&input[*i], "<<", 2) == 0)
		type = T_DLESS;
	else if (strncmp(&input[*i], ">>", 2) == 0)
		type = T_DGREAT;
	else if (strncmp(&input[*i], "&&", 2) == 0)
		type = T_AND;
	else if (strncmp(&input[*i], "||", 2) == 0)
		type = T_OR;
	else
		return (1);
	value = ft_strndup(&input[*i], len);
	if (!value)
		return (1);
	new_tok = new_token(value, type, NO_QUOTE);
	if (!new_tok)
		return (free(value), 1);
	if (add_token_to_list(lst, new_tok))
		return (free(value), free(new_tok), 1);
	(*i) += len;
	return (0);
}

int	single_special(char *input, int *i, t_token **lst, int len)
{
	t_token_type	type;
	t_token			*new_tok;
	char			*value;

	if (input[*i] == '<')
		type = T_LESS;
	else if (input[*i] == '>')
		type = T_GREAT;
	else if (input[*i] == '|')
		type = T_PIPE;
	else
		return (1);
	value = ft_strndup(&input[*i], len);
	if (!value)
		return (1);
	new_tok = new_token(value, type, NO_QUOTE);
	if (!new_tok)
		return (free(value), 1);
	if (add_token_to_list(lst, new_tok))
		return (free(value), free(new_tok), 1);
	(*i) += len;
	return (0);
}

int	token_add(char *input, int *i, t_token **lst, t_data *data)
{
	int	len;

	len = is_special_char(&input[*i]);
	if (len == 2 && is_special_char(&input[*i]))
	{
		if (double_special(input, i, lst, len) == 1)
			return (1);
		return (0);
	}
	else if (len == 1 && is_special_char(&input[*i]))
	{
		if (single_special(input, i, lst, len) == 1)
			return (1);
		return (0);
	}
	else
		return (add_identifier(input, i, lst, data));
}
