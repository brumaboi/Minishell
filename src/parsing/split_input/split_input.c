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

#include "../../../inc/minishell.h"

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

int handle_normal(const char *str, int *i, t_norm_split *norm)
{
    const char *end;

    end = find_token_end(&str[*i]);
    if (!end || end <= &str[*i])
        return (free_split(norm->result), free_tokens(*norm->lst), 0);
    norm->result[norm->idx] = copy_token(&str[*i], end, norm->data);
    if (!norm->result[norm->idx])
        return (free_split(norm->result), free_tokens(*norm->lst), 0);
    if (token_add((char *)str, i, norm->lst, norm->data))
        return (free_split(norm->result), free_tokens(*norm->lst), 0);
    norm->idx++;
    *i = end - str;
    return (1);
}

int handle_special(const char *str, int *i, t_norm_split *norm)
{
    int len;

    len = is_special_char(&str[*i]);
    if (len > 0)
    {
        if (token_add((char *)str, i, norm->lst, norm->data))
            return (free_split(norm->result), free_tokens(*norm->lst), 0);
        norm->result[norm->idx] = ft_strndup(&str[*i - len], len);
        if (!norm->result[norm->idx])
            return (free_split(norm->result), free_tokens(*norm->lst), 0);
        norm->idx++;
        return (1);
    }
    return (0);
}

static int process_split(const char *str, t_norm_split *norm)
{
    int i;

    i = 0;
    while (str[i])
    {
        while (ft_isspace(str[i]))
            i++;
        if (str[i] == '\0')
            break ;
        if (handle_special(str, &i, norm))
            continue ;
        if (!handle_normal(str, &i, norm))
            return (0);
    }
    return (1);
}

char **split_input(const char *str, int *count, t_token **lst, t_data *data)
{
    int spaces;
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
    if (!process_split(str, &norm))
        return (free_split(norm.result), free_tokens(*norm.lst), NULL);
    norm.result[norm.idx] = NULL;
    *count = norm.idx;
    return (norm.result);
}
