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

// Function to toggle quote states and handle escape sequences
int quote_state_and_escape(const char *str, int *in_single_quote, int *in_double_quote)
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
        if (*start == '\\' && *(start + 1) && !in_single_quote)
        {
            start += 2;
            continue;
        }
        if (*start == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (*start == '"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        if (!in_single_quote && !in_double_quote && (is_special_char(start) || ft_isspace(*start)))
            break;
        start++;
    }
    if (in_single_quote || in_double_quote)
    {
        write(2, "syntax error: unmatched quote\n", 30);
        return NULL;
    }
    return start;
}

char **split_input(const char *str, int *count, t_token **lst, t_data *data)
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
        while (ft_isspace(str[i])) // Skip leading whitespace
            i++;
        if (str[i] == '\0')
            break;
        int len = is_special_char(&str[i]);
        if (len > 0) // Handle special characters
        {
            if (token_add((char *)str, &i, lst)) // Add special token to list
                return (free_split(result), free_tokens(*lst), NULL);
            result[idx] = strndup(&str[i - len], len); // Copy the special character token
            if (!result[idx])
                return (free_split(result), NULL);
            idx++;
            continue ; // Skip further processing for this token
        }
        end = find_token_end(&str[i]);
        if (!end || end <= &str[i])  // Safeguard to prevent infinite loop
            break ;
        result[idx] = copy_token(&str[i], end, data); // Copy non-special token
        if (!result[idx])
            return (free_split(result), NULL);
        if (token_add((char *)str, &i, lst)) // Add the identifier token to the list
            return (free_split(result), free_tokens(*lst), NULL);
        idx++;
        i = end - str; // Update index to the end of the processed token
    }
    result[idx] = NULL;
    *count = idx;
    return (result);
}
