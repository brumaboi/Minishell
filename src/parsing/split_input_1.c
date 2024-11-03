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
int	quote_state_and_escape(const char *str, int *in_single_quote, int *in_double_quote)
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

static const char *find_token_end(const char *start)
{
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (*start)
    {
        if (quote_state_and_escape(start, &in_single_quote, &in_double_quote))
        {
            start++;
            continue ;
        }
        if (!in_single_quote && !in_double_quote && is_special_char(start))
            break ;
        if (ft_isspace(*start) && !in_single_quote && !in_double_quote)
            break ;  // Stop at whitespace outside quotes
        start++;
    }
    if (validate_quotes(in_single_quote, in_double_quote))
        return NULL;
    return start;
}

char **split_input(const char *str, int *count, t_token **lst)
{
    int spaces;
    char **result;
    int idx;
    const char *end;
    int i;

    idx = 0;
    i = 0;
    if (!str || *str == '\0')
    {
        *count = 0;
        return (NULL);
    }
    spaces = count_delimiters(str);
    result = malloc((spaces + 2) * sizeof(char *));
    if (!result)
        return (NULL);
    while (str[i])
    {
        while (ft_isspace(str[i]))
            i++;
        if (str[i] == '\0')
            break;
        if (is_special_char(&str[i]))
        {
            if (token_add((char *)str, i, lst))
                return (free_split(result), free_tokens(*lst), NULL);
            result[idx] = malloc(2 * sizeof(char));
            if (!result[idx])
                return (free_split(result), NULL);
            result[idx][0] = str[i];
            result[idx][1] = '\0';
            idx++;
            i++;
            continue ;
        }
        end = find_token_end(&str[i]);
        if (!end || end <= &str[i])  // Safeguard to prevent infinite loop
            break;
        result[idx] = copy_token(&str[i], end);
        if (!result[idx])
            return (free_split(result), NULL);
        idx++;  // Increment `idx` to count the newly added token
        if (token_add((char *)str, i, lst))
            return (free_split(result), free_tokens(*lst), NULL);
        i = end - str;
    }
    result[idx] = NULL;
    *count = idx;  // Update the total token count
    return (result);
}
