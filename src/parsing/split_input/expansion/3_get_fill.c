/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:41:00 by marvin            #+#    #+#             */
/*   Updated: 2024/12/06 18:41:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

static void	copy_fill(const char **ptr, char **result, t_data *data)
{
	char	*env_value;

	env_value = expand_env_var(*ptr, data);
	if (env_value)
	{
		ft_strcpy(*result, env_value);
		*result += ft_strlen(env_value);
		free(env_value);
	}
	while (**ptr && (ft_isalnum(**ptr) || **ptr == '_'))
		(*ptr)++;
}

void	process_question_mark(char **result, t_data *data, const char **ptr)
{
	char	*status_str;

	status_str = ft_itoa(data->exit_status);
	if (status_str)
	{
		ft_strcpy(*result, status_str);
		*result += ft_strlen(status_str);
		free(status_str);
	}
	(*ptr)++;
}

void	handle_dollar(const char **ptr, char **result, t_data *data, int in_single_quote)
{
	if (**ptr == '$' && !in_single_quote)
	{
		(*ptr)++;
		if (**ptr == '\0')
		{
			*(*result)++ = '$';
		}
		else if (**ptr == '?')
		{
			process_question_mark(result, data, ptr);
		}
		else if (ft_isalnum(**ptr) || **ptr == '_')
		{
			copy_fill(ptr, result, data);
		}
		else
		{
			*(*result)++ = '$';
			if (**ptr)
				*(*result)++ = *(*ptr)++;
		}
	}
}

int	toggle_quotes(const char **ptr, int quote_state[2])
{
	if (**ptr == '"' && !quote_state[0])
	{
		quote_state[1] = !quote_state[1];
		(*ptr)++;
		return (1);
	}
	if (**ptr == '\'' && !quote_state[1])
	{
		quote_state[0] = !quote_state[0];
		(*ptr)++;
		return (1);
	}
	return (0);
}

void	fill_expanded(const char *token, char *expanded, t_data *data)
{
	const char	*ptr;
	char		*result;
	int			quote_state[2];

	ptr = token;
	result = expanded;
	quote_state[0] = 0;
	quote_state[1] = 0;
	while (*ptr)
	{
		if (toggle_quotes(&ptr, quote_state))
			continue ;
		if (*ptr == '$' && !quote_state[0])
		{
			handle_dollar(&ptr, &result, data, quote_state[0]);
			continue ;
		}
		*result++ = *ptr++;
	}
	*result = '\0';
}
