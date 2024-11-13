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
    if (type == T_IDENTIFIER)
    {
        if (!value)
            return (free(token), NULL);
        token->value = value;
    }
    else
        token->value = NULL;
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
        return (1);
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

int token_add(char *input, int i, t_token **lst)
{
    char *value;
    int start = i;

    if (input[i] == '>' && input[i + 1] == '>')
    {
        i += 2;
        return (add_token_to_list(lst, T_DGREAT, &i, NULL));
    }
    else if (input[i] == '>')
    {
        i++;
        return (add_token_to_list(lst, T_GREAT, &i, NULL));
    }
    else if (input[i] == '<' && input[i + 1] == '<')
    {
        i += 2;
        return (add_token_to_list(lst, T_DLESS, &i, NULL));
    }
    else if (input[i] == '<')
    {
        i++;
        return (add_token_to_list(lst, T_LESS, &i, NULL));
    }
    else if (input[i] == '|' && input[i + 1] == '|')
    {
        i += 2;
        return (add_token_to_list(lst, T_OR, &i, NULL));
    }
    else if (input[i] == '|')
    {
        i++;
        return (add_token_to_list(lst, T_PIPE, &i, NULL)); // Fix: Assign a valid value
    }
    else if (input[i] == '&' && input[i + 1] == '&')
    {
        i += 2;
        return (add_token_to_list(lst, T_AND, &i, NULL));
    }
    else if (input[i] == '(')
    {
        i++;
        return (add_token_to_list(lst, T_OPAR, &i, NULL)); // Fix: Assign a valid value
    }
    else if (input[i] == ')')
    {
        i++;
        return (add_token_to_list(lst, T_CPAR, &i, NULL)); // Fix: Assign a valid value
    }
    else
    {
        // Check for quoted strings
        if (input[i] == '"' || input[i] == '\'')
        {
            char quote_char = input[i];
            i++; // Skip the opening quote
            start = i; // Mark the start of the quoted content
            while (input[i] && input[i] != quote_char)
                i++;

            if (input[i] == quote_char)
                i++;
        }
        else
        {
            while (input[i] && !ft_isspace(input[i]) && !is_special_char(&input[i]))
                i++;
        }
        int length = i - start;
        if (input[i - 1] == '"' || input[i - 1] == '\'')
        {
            length -= 1; // Exclude the closing quote from the token value
        }
        value = ft_substr(input, start, length);
        if (!value)
            return (1);
        return (add_token_to_list(lst, T_IDENTIFIER, &i, value));
    }
}
