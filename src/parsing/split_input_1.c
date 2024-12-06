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

typedef struct s_norm_split
{
    char **result;
    t_token **lst;
    int idx;
    t_data *data;
} t_norm_split;

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

int handle_normal(const char *str, int *i, t_norm_split *norm)
{
    const char *end;
    
    end = find_token_end(&str[*i]);
    if (!end || end <= &str[*i])
        return (free_split(norm->result), free_tokens(*norm->lst), 0);
    norm->result[norm->idx] = copy_token(&str[*i], end, norm->data);
    if (!norm->result[norm->idx]) // Memory allocation failure
        return (free_split(norm->result), free_tokens(*norm->lst), 0);
    if (token_add((char *)str, i, norm->lst)) // Error during token addition
        return (free_split(norm->result), free_tokens(*norm->lst), 0);
    norm->idx++;
    *i = end - str;
    return (1); // Normal token processed
}

int handle_special(const char *str, int *i, t_norm_split *norm)
{
    int len;
    
    len = is_special_char(&str[*i]);
    if (len > 0)
    {
        if (token_add((char *)str, i, norm->lst)) // Error during token addition
            return (free_split(norm->result), free_tokens(*norm->lst), 0);
        norm->result[norm->idx] = strndup(&str[*i - len], len);
        if (!norm->result[norm->idx]) // Memory allocation failure
            return (free_split(norm->result), free_tokens(*norm->lst), 0);
        norm->idx++;
        return (1); // Special token processed
    }
    return (0); // Not a special token
}

char **split_input(const char *str, int *count, t_token **lst, t_data *data)
{
    int spaces;
    int i;
    t_norm_split norm;

    norm.idx = 0;
    norm.lst = lst;
    norm.data = data;
    if (!str || *str == '\0')
    {
        *count = 0;
        return (NULL);
    }
    spaces = count_delimiters(str);
    norm.result = malloc((spaces + 2) * sizeof(char *));
    if (!norm.result)
        return (NULL);
    i = 0;
    while (str[i])
    {
        while (ft_isspace(str[i]))
            i++;
        if (str[i] == '\0')
            break ;
        if (handle_special(str, &i, &norm))
            continue ;
        if (!handle_normal(str, &i, &norm))
            return (free_split(norm.result), free_tokens(*norm.lst), NULL);
    }
    norm.result[norm.idx] = NULL;
    *count = norm.idx;
    return (norm.result);
}
