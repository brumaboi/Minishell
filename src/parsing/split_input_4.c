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

#include "../../inc/minishell.h"
//token_list_management

static t_token *new_token(char *value, t_token_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    if (value == NULL)
        return (free(token), NULL);
    token->value = value;
    token->type = type;
    token->next = NULL;
    return (token);
}

static int add_token_to_list(t_token **lst, t_token_type type, int *i, char *value)
{
    t_token *new;
    t_token *last;

    if (type == T_IDENTIFIER && value == NULL)
        return (1);
    new = new_token(value, type);
    if (!new)
        return (free(value), 1);
    if (*lst == NULL)
        *lst = new;
    else
    {
        last = *lst;
        while (last->next)
            last = last->next;
        last->next = new;
    }
    if (type == T_OPAR || type == T_CPAR || type == T_PIPE || type == T_GREAT || type == T_LESS)
        (*i)++;
    else if (type == T_DGREAT || type == T_DLESS || type == T_OR || type == T_AND)
        (*i) += 2;
    return (0);
}

int add_identifier(char *input, int *i, t_token **lst)
{
    char *value;
    int start;
    char quote_char;
    int length;

    start = *i;
    if (input[*i] == '"' || input[*i] == '\'')
    {
        quote_char = input[*i];
        (*i)++;
        start = *i;
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
    length = *i - start;
    if (input[*i - 1] == '"' || input[*i - 1] == '\'')
        length -= 1;
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
 