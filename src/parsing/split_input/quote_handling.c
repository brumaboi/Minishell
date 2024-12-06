/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:05:57 by marvin            #+#    #+#             */
/*   Updated: 2024/12/06 19:05:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

const char *find_token_end(const char *start)
{
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (*start)
    {
        if (*start == '\\' && *(start + 1) && !in_single_quote)
        {
            start += 2;
            continue ;
        }
        if (*start == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (*start == '"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        if (!in_single_quote && !in_double_quote && (is_special_char(start) || ft_isspace(*start)))
            break ;
        start++;
    }
    if (in_single_quote || in_double_quote)
    {
        write(2, "syntax error: unmatched quote\n", 30);
        return (NULL);
    }
    return (start);
}
