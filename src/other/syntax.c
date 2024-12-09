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

int handle_initial_conditions(const char *input)
{
    int i = 0;
    if (!input || *input == '\0')
        return (0); // Empty input is valid but does nothing
    while (input[i] && ft_isspace(input[i]))
        i++;
    if (is_special_char(&input[i]) > 0 && input[i] != '(') // Starts with operator
    {
        fprintf(stderr, " syntax error near unexpected token `%c'\n", input[i]);
        return (1);
    }
    return (i);
}

int handle_quotes_and_special_chars(const char *input, int *i, int *in_single_quote, int *in_double_quote)
{
    if (input[*i] == '\'' && !(*in_double_quote)) // Toggle single quote
        *in_single_quote = !(*in_single_quote);
    else if (input[*i] == '"' && !(*in_single_quote)) // Toggle double quote
        *in_double_quote = !(*in_double_quote);
    if (!(*in_single_quote) && !(*in_double_quote)) // Outside of quotes
    {
        int len = is_special_char(&input[*i]);
        if (len > 0)
        {
            if (is_special_char(&input[*i + len]) > 0) // Consecutive operators
            {
                fprintf(stderr, " syntax error near unexpected token `%.*s'\n", len, &input[*i]);
                return (1);
            }
            *i += len - 1;
        }
    }
    return (0);
}

int handle_unmatched_quotes(int in_single_quote, int in_double_quote)
{
    if (in_single_quote || in_double_quote)
    {
        fprintf(stderr, " syntax error: unmatched quote\n");
        return (1);
    }
    return (0);
}

int handle_trailing_conditions(const char *input, int i)
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

int correct_syntax(const char *input)
{
    int i = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;;

    i = handle_initial_conditions(input);
    if (i == 1)
        return (2);
    while (input[i])
    {
        if (handle_quotes_and_special_chars(input, &i, &in_single_quote, &in_double_quote))
            return (2);
        i++;
    }
    if (handle_unmatched_quotes(in_single_quote, in_double_quote))
        return (2);
    return (handle_trailing_conditions(input, i - 1));
}
