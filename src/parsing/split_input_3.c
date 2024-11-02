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

#include "../../inc/minishell.h"
//expand 

static char *expand_env_var(const char *input)
{
    char *var_name;
	char *env_value;
	int var_len;

	var_len = 0;
	while (input[var_len] && (ft_isalnum(input[var_len]) || input[var_len] == '_'))
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

static char *expand_token(const char *token)
{
	char *expanded;
	char *result;
	const char *ptr;
	char *env_value;

	expanded = malloc(ft_strlen(token) + 1);
	result = expanded;
	ptr = token;
	if (!expanded)
		return (NULL);
	while (*ptr)
	{
		if (*ptr == '$')
		{
			ptr++;
			env_value = expand_env_var(ptr);
			if (!env_value)
				continue ;
			ft_strcpy(result, env_value);
			result += ft_strlen(env_value);
			free(env_value);
			while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
				ptr++;
		}
		else
		{
			*result = *ptr;
			result++;
			ptr++;
		}
	}
	*result = '\0';
	return (expanded);
}

// Function to allocate and copy token content
char	*copy_token(const char *start, const char *end)
{
	char	*result;
	int		in_single_quote = 0;
	int		in_double_quote = 0;
	int		i = 0;
    char    *expanded_result;

	result = malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (start < end)
	{
		if (quote_state_and_escape(start, &in_single_quote, &in_double_quote))
		{
			start++;
			result[i++] = *start;
		}
		else if ((*start != '\'' && *start != '"') || (in_single_quote || in_double_quote))
			result[i++] = *start;
		start++;
	}
	result[i] = '\0';
    expanded_result = expand_token(result);
    free(result);
    return (expanded_result);
}
