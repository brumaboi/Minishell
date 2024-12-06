/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:56:36 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 21:56:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int get_length(char *input, int *i, int *start)
{
    char quote_char;
    int len;

    *start = *i;
    if (input[*i] == '"' || input[*i] == '\'')
    {
        quote_char = input[*i];
        (*i)++;
        *start = *i;
        while (input[*i] && input[*i] != quote_char)
            (*i)++;
        if (input[*i] == quote_char)
            (*i)++;
    }
    else
    {
        while (input[*i] && !ft_isspace(input[*i]) && !is_special_char(&input[*i]))
            (*i)++;
    }
    len = *i - *start;
    if (input[*i - 1] == '"' || input[*i - 1] == '\'')
        len -= 1;
    return (len);
}

int add_identifier(char *input, int *i, t_token **lst)
{
    char *value;
    int start;
    int length;

    length = get_length(input, i, &start);
    value = ft_substr(input, start, length);
    if (!value)
        return (1);
    return (add_token_to_list(lst, T_IDENTIFIER, i, value));
}

int double_special(char *input, int *i, t_token **lst, int len)
{
    t_token_type type;
    char *value;

    if (strncmp(&input[*i], "<<", 2) == 0)
        type = T_DLESS;
    else if (strncmp(&input[*i], ">>", 2) == 0)
        type = T_DGREAT;
    else if (strncmp(&input[*i], "&&", 2) == 0)
        type = T_AND;
    else if (strncmp(&input[*i], "||", 2) == 0)
        type = T_OR;
    else
        return (1);
    value = ft_strndup(&input[*i], len); // Extract the token value (e.g., "<<")
    if (!value)
        return (1);
    if (add_token_to_list(lst, type, i, value)) // If adding fails
    {
        free(value); // Free the allocated memory
        return (1);
    }
    return (0);
}

int single_special(char *input, int *i, t_token **lst, int len)
{
    t_token_type type;
    char *value;

    if (input[*i] == '<')
        type = T_LESS;
    else if (input[*i] == '>')
        type = T_GREAT;
    else if (input[*i] == '|')
        type = T_PIPE;
    else if (input[*i] == '(')
        type = T_OPAR;
    else if (input[*i] == ')')
        type = T_CPAR;
    else
        return (1);
    value = ft_strndup(&input[*i], len); // Extract the token value (e.g., "<")
    if (!value)
        return (1);
    if (add_token_to_list(lst, type, i, value)) // If adding fails
    {
        free(value); // Free the allocated memory
        return (1);
    }
    return (0);
}

int token_add(char *input, int *i, t_token **lst)
{
    int len;

    len = is_special_char(&input[*i]); // Check for special character length
    if (len == 2 && is_special_char(&input[*i])) // Compound tokens like <<, >>
    {
        if (double_special(input, i, lst, len) == 1)
            return (1);
        return(0);
    }
    else if (len == 1 && is_special_char(&input[*i])) // Single-character tokens
    {
        if (single_special(input, i, lst, len) == 1)
            return (1);
        return(0);
    }
    else // Handle identifiers or literals
        return (add_identifier(input, i, lst));
}
 