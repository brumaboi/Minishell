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

t_token *new_token(char *value, t_token_type type)
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

int add_token_to_list(t_token **lst, t_token_type type, int *i, char *value)
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
