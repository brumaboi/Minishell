/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:41:00 by marvin            #+#    #+#             */
/*   Updated: 2024/12/06 18:41:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

static void handle_quotes_fill(const char **ptr, char **result, int *in_single_quote, int *in_double_quote)
{
    if (quote_state_and_escape(*ptr, in_single_quote, in_double_quote))
    {
        *(*result)++ = *(*ptr)++;
    }
}

static void copy_fill(const char **ptr, char **result, const char *token, t_data *data)
{
    char *env_value;

    if (strcmp(token, "$") == 0)
    {
        *(*result)++ = '$'; // Copy "$" as is
        return;
    }
    env_value = expand_env_var(*ptr, data);
    if (env_value)
    {
        ft_strcpy(*result, env_value); // Safe copy
        *result += ft_strlen(env_value);
        free(env_value);
    }
    while (**ptr && (ft_isalnum(**ptr) || **ptr == '_'))
        (*ptr)++;
}

void fill_expanded(const char *token, char *expanded, t_data *data)
{
    const char *ptr;
    char *result;
    int in_single_quote;
    int in_double_quote;

    result = expanded;
    ptr = token;
    in_single_quote = 0;
    in_double_quote = 0;
    while (*ptr)
    {
        handle_quotes_fill(&ptr, &result, &in_single_quote, &in_double_quote);
        if (*ptr == '$' && !in_single_quote)
        {
            ptr++;
            copy_fill(&ptr, &result, token, data);
            continue ;
        }
        if (*ptr)
            *result++ = *ptr++;
    }
    *result = '\0'; // Null-terminate the expanded string
}
