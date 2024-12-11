/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:55:42 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 21:55:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

char	*expand_env_var(const char *input, t_data *data)
{
	char	*var_name;
	char	*env_value;
	int		var_len;

	if (*input == '?' && *(input + 1) == '\0')
	{
		return (ft_itoa(data->exit_status));
	}
	var_len = 0;
	while (input[var_len] && (ft_isalnum(input[var_len])
			|| input[var_len] == '_'))
		var_len++;
	if (var_len == 0)
		return (NULL);
	var_name = ft_strndup(input, var_len);
	if (!var_name)
		return (NULL);
	env_value = getenv(var_name);
	free(var_name);
	if (!env_value)
		return (ft_strdup(""));
	return (ft_strdup(env_value));
}

char	*expand_token(const char *token, t_data *data)
{
	char	*expanded;
	size_t	total_length;

	total_length = get_expansion_len(token, data);
	expanded = malloc(total_length + 1);
	if (!expanded)
		return (NULL);
	fill_expanded(token, expanded, data);
	return (expanded);
}

static char	*good_result(char *result, t_data *data, int in_single_quotes)
{
	char	*expanded_result;

	if (!in_single_quotes)
	{
		expanded_result = expand_token(result, data);
		free(result);
		return (expanded_result);
	}
	return (result);
}

char	*parse_content(const char *ptr, const char *end,
						char *result, int *quotes)
{
	int	idx;

	idx = 0;
	while (ptr < end)
	{
		if (*ptr == '\'' && !quotes[1])
		{
			quotes[0] = !quotes[0];
			ptr++;
			continue ;
		}
		else if (*ptr == '"' && !quotes[0])
		{
			quotes[1] = !quotes[1];
			ptr++;
			continue ;
		}
		else if (*ptr == '\\' && *(ptr + 1) && !quotes[0])
		{
			ptr++;
			result[idx++] = *ptr;
		}
		else
		{
			result[idx++] = *ptr;
		}
		ptr++;
	}
	result[idx] = '\0';
	return (result);
}

char	*copy_token(const char *start, const char *end, t_data *data)
{
	char		*result;
	int			quotes[2];
	const char	*ptr;

	quotes[0] = 0;
	quotes[1] = 0;
	ptr = start;
	if (*start == '\'' && *(end - 1) == '\'')
	{
		quotes[0] = 1;
		ptr++;
		end--;
	}
	result = malloc((end - ptr + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result = parse_content(ptr, end, result, quotes);
	return (good_result(result, data, quotes[0]));
}
