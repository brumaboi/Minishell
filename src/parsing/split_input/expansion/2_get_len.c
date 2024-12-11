/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_get_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:38:58 by marvin            #+#    #+#             */
/*   Updated: 2024/12/06 18:38:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

static size_t	handle_env_var(const char **ptr, const char **token, t_data *data)
{
	char	*env_value;
	size_t	total_length;

	total_length = 0;
	if (**ptr == '\0' || (!ft_isalnum(**ptr) && **ptr != '_'))
	{
		total_length++;
		(*token) = *ptr;
		return (total_length);
	}
	env_value = expand_env_var(*ptr, data);
	if (env_value)
	{
		total_length += ft_strlen(env_value);
		free(env_value);
	}
	while (**ptr && (ft_isalnum(**ptr) || **ptr == '_'))
		(*ptr)++;
	*token = *ptr;
	return (total_length);
}

static size_t	handle_quotes_len(const char **ptr, int *in_single_quote, int *in_double_quote)
{
	if (quote_state_and_escape(*ptr, in_single_quote, in_double_quote))
	{
		(*ptr)++;
		return (1);
	}
	return (0);
}

size_t	get_expansion_len(const char *token, t_data *data)
{
	const char	*ptr;
	int			in_single_quote;
	int			in_double_quote;
	size_t		total_length;

	total_length = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	ptr = token;
	while (*ptr)
	{
		if (handle_quotes_len(&ptr, &in_single_quote, &in_double_quote))
			continue ;
		if (*ptr == '$' && !in_single_quote)
		{
			ptr++;
			total_length += handle_env_var(&ptr, &token, data);
			continue ;
		}
		total_length++;
		ptr++;
	}
	return (total_length);
}
