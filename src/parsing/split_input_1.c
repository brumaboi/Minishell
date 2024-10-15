/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:44:48 by marvin            #+#    #+#             */
/*   Updated: 2024/10/11 16:44:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Function to validate unmatched quotes
static int	validate_quotes(int in_single_quote, int in_double_quote)
{
	if (in_single_quote || in_double_quote)
	{
		write(2, "syntax error: unmatched quote\n", 30);
		return (1);
	}
	return (0);
}

// Handles quote toggling and escape sequences
static int	quote_state_and_escape(const char *str, int *in_single_quote, int *in_double_quote)
{
	if (*str == '\\' && *(str + 1) && !*in_single_quote)
		return (1);
	if (*str == '"' && !*in_single_quote)
		*in_double_quote = !*in_double_quote;
	else if (*str == '\'' && !*in_double_quote)
		*in_single_quote = !*in_single_quote;
	return (0);
}

static int	count_delimiters(const char *str)
{
	int	spaces;
	int	in_single_quote;
	int	in_double_quote;

	spaces = 0;
	in_single_quote = 0;
	in_double_quote = 0;
    while (*str)
	{
		if (quote_state_and_escape(str, &in_single_quote, &in_double_quote))
			str++;
		else if (ft_isspace(*str) && !in_single_quote && !in_double_quote)
			spaces++;
		else if (is_special_char(str) && !in_single_quote && !in_double_quote)
			spaces++;
		str++;
	}
	return (spaces);
}

static const char	*find_token_end(const char *start)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*start && (in_single_quote || in_double_quote || (!ft_isspace(*start) && !is_special_char(start))))
	{
		if (quote_state_and_escape(start, &in_single_quote, &in_double_quote))
			start++;
		start++;
	}
	if (validate_quotes(in_single_quote, in_double_quote)) 
		return (NULL);
	return (start);
}

char **split_input(const char *str, int *count, t_token **lst)
{
    int spaces;
    char **result;
    int idx;
    const char *end;

    idx = 0;
    spaces = count_delimiters(str);
    result = malloc((spaces + 2) * sizeof(char *));
    if (!result)
        return (NULL); /// should make a function to handle errors
    while (*str)
    {
        while (ft_isspace(*str))
            str++;
        if (is_special_char(str))
        {
            result[idx++] = process_special_char(str);
            str += special_char_len(str);
        }
        else if (*str)
        {
            end = find_token_end(str);
            if(!end)
                return (NULL); /// should make a function to handle errors
            result[idx++] = copy_token(str, end);
            token_add((char *)str, (int *)&idx, lst);
            str = end;
        }
    }
    result[idx] = NULL;
    *count = idx;
    return (result);
}
