/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:59:05 by marvin            #+#    #+#             */
/*   Updated: 2024/12/06 18:59:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

t_token *new_token(char *value, t_token_type type, t_quote_type quote_type)
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
    token->quote_type = quote_type;
    return (token);
}

int add_token_to_list(t_token **lst, t_token *new)
{
    t_token *last;

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
    return (0);
}
