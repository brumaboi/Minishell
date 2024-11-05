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

// Create a new token and add it to the list
static t_token *new_token(char *value, t_token_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->value = value;
    token->type = type;
    token->next = NULL;
    return (token);
}

// Add a token to the end of the list
static int add_token_to_list(t_token **lst, t_token_type type, int *i, char *value)
{
    t_token *new;
    t_token *last;

    // If the type is T_IDENTIFIER, ensure we pass the value
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
        return (add_token_to_list(lst, T_PIPE, &i, ft_strdup("|"))); // Fix: Assign a valid value
    }
    else if (input[i] == '&' && input[i + 1] == '&')
    {
        i += 2;
        return (add_token_to_list(lst, T_AND, &i, NULL));
    }
    else if (input[i] == '(')
    {
        i++;
        return (add_token_to_list(lst, T_OPAR, &i, ft_strdup("("))); // Fix: Assign a valid value
    }
    else if (input[i] == ')')
    {
        i++;
        return (add_token_to_list(lst, T_CPAR, &i, ft_strdup(")"))); // Fix: Assign a valid value
    }
    else
    {
        while (input[i] && !ft_isspace(input[i]) && !is_special_char(&input[i]))
            i++;
        value = ft_substr(input, start, i - start);
        if (!value)
            return (1);
        return (add_token_to_list(lst, T_IDENTIFIER, &i, value));
    }
}
