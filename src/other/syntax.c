/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:47:18 by marvin            #+#    #+#             */
/*   Updated: 2024/12/07 23:47:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_initial_conditions(const char *input)
{
	int	i;

	i = 0;
	if (!input || *input == '\0')
		return (0);
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (0);
	if (is_special_char(&input[i]) > 0 && input[i] != '(')
	{
		fprintf(stderr, " syntax error near unexpected token `%c'\n", input[i]);
		return (1);
	}
	return (i);
}

int	handle_special_chars(const char *input, int *i)
{
	int	len;
	int	j;

	len = is_special_char(&input[*i]);
	if (len > 0)
	{
		j = *i + len;
		while (ft_isspace(input[j]))
			j++;
		if (is_special_char(&input[j]) > 0)
		{
			fprintf(stderr, " syntax error near unexpected token `%.*s'\n",
				len, &input[*i]);
			return (1);
		}
		*i += len - 1;
	}
	return (0);
}

int	handle_quotes_and_special_chars(const char *input, int *i,
									int *in_single_quote, int *in_double_quote)
{
	if (input[*i] == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (input[*i] == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	if ((*in_single_quote || *in_double_quote) && input[*i + 1] == '\0')
		return (fprintf(stderr, " syntax error: unmatched quote\n"), 1);
	if (!(*in_single_quote) && !(*in_double_quote))
		return (handle_special_chars(input, i));
	return (0);
}

int	handle_trailing_conditions(const char *input, int i)
{
	while (i >= 0 && ft_isspace(input[i]))
		i--;
	if (is_special_char(&input[i]) > 0 && input[i] != ')')
	{
		fprintf(stderr, " syntax error near unexpected token `%c'\n", input[i]);
		return (2);
	}
	return (0);
}

int	correct_syntax(const char *input)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	i = handle_initial_conditions(input);
	if (i == 1)
		return (2);
	if (i == 0)
	{
		if (!input || *input == '\0' || many_spaces(input))
			return (0);
	}
	while (input[i])
	{
		if (handle_quotes_and_special_chars(input, &i,
				&in_single_quote, &in_double_quote))
			return (2);
		i++;
	}
	if (handle_unmatched_quotes(in_single_quote, in_double_quote))
		return (2);
	return (handle_trailing_conditions(input, i - 1));
}
