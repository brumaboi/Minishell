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

static const char	*find_token_end(const char *start)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*start && (in_single_quote || in_double_quote
			|| (!ft_isspace(*start) && !is_special_char(start))))
	{
		if (*start == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*start == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
        else if (*start == '\\' && *(start + 1))
            start++;
		start++;
	}
	return (start);
}

static int	count_spaces(const char *str)
{
	int	spaces;
	int	in_single_quote;
	int	in_double_quote;

	spaces = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (*str)
	{
		if (*str == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*str == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (ft_isspace(*str) && !in_single_quote && !in_double_quote)
			spaces++;
        else if((*str == '|' || *str == '<' || *str == '>') && !in_single_quote && !in_double_quote)
            spaces++;
		str++;
	}
	return (spaces);
}

static char	*allocate_and_copy(const char *start, const char *end)
{
	char	*result;
	int		in_single_quote;
	int		in_double_quote;
	int		i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	result = malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (NULL); /// should make a function to handle errors
	while (start < end)
	{
		if (*start == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*start == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
        else if (*start == '\\'  && *(start + 1) && !in_single_quote && !in_double_quote)
        {
            start++;
            result[i++] = *start;
        }
		else
			result[i++] = *start;
		start++;
	}
	result[i] = '\0';
	return (result);
}

static char *allocate_special_char(const char *str)
{
    char *result;
    int len;

    len = special_char_len(str);
    result = malloc((len + 1) * sizeof(char));
    if (!result)
        return (NULL); /// should make a function to handle errors
    ft_strncpy(result, str, len);
    result[1] = '\0';
    return (result);
}

int is_special_char(const char *str)
{
    if (*str == '|' || *str == '<' || *str == '>' || *str == ';' || *str == '&') 
        return (1);
    if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0
        || ft_strncmp(str, "&&", 2) == 0 || ft_strncmp(str, "||", 2) == 0)
        return (1);
    return (0);
}

int special_char_len(const char *str)
{
    if (*str == '|' || *str == '<' || *str == '>' || *str == ';' || *str == '&') 
        return (1);
    return (2);
}

char **split_string(const char *str, int *count)
{
    int spaces;
    char **result;
    int idx;
    const char *end;

    idx = 0;
    spaces = count_spaces(str);
    result = malloc((spaces + 2) * sizeof(char *));
    if (!result)
        return (NULL); /// should make a function to handle errors
    while (*str)
    {
        while (ft_isspace(*str))
            str++;
        if (is_special_char(str))
        {
            result[idx++] = allocate_special_char(str);
            str += special_char_len(str);
        }
        else if (*str)
        {
            end = find_token_end(str);
            result[idx++] = allocate_and_copy(str, end);
            str = end;
        }
    }
    result[idx] = NULL;
    *count = idx;
    return (result);
}
