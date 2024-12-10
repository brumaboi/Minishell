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

// static void handle_quotes_fill(const char **ptr, char **result, int *in_single_quote, int *in_double_quote)
// {
//     if (**ptr == '\'' && !*in_double_quote)
//     {
//         *in_single_quote = !*in_single_quote;
//         (*ptr)++;
//     }
//     else if (**ptr == '"' && !*in_single_quote)
//     {
//         *in_double_quote = !*in_double_quote;
//         (*ptr)++;
//     }
//     else if (**ptr == '$' && *in_single_quote)
//     {
//         *(*result)++ = *(*ptr)++;
//     }
// }

static void copy_fill(const char **ptr, char **result, t_data *data)
{
    char *env_value;

    env_value = expand_env_var(*ptr, data);
    if (env_value)
    {
        ft_strcpy(*result, env_value);
        *result += ft_strlen(env_value);
        free(env_value);
    }
    while (**ptr && (ft_isalnum(**ptr) || **ptr == '_'))
        (*ptr)++;
}

void process_question_mark(char **result, t_data *data, const char **ptr)
{
    char *status_str;

    status_str = ft_itoa(data->exit_status);
    if (status_str)
    {
        ft_strcpy(*result, status_str);
        *result += ft_strlen(status_str);
        free(status_str);
    }
    (*ptr)++;
}

void handle_dollar(const char **ptr, char **result, t_data *data, int in_single_quote)
{
    if (**ptr == '$' && !in_single_quote)
    {
        (*ptr)++;
        if (**ptr == '\0')
        {
            *(*result)++ = '$';
        }
        else if (**ptr == '?')
        {
            process_question_mark(result, data, ptr);
        }
        else if (ft_isalnum(**ptr) || **ptr == '_')
        {
            copy_fill(ptr, result, data);
        }
        else
        {
            *(*result)++ = '$';
            if (**ptr)
                *(*result)++ = *(*ptr)++;
        }
    }
}

void fill_expanded(const char *token, char *expanded, t_data *data)
{
    const char *ptr;
    char *result;
    int in_single_quote;
    int in_double_quote;

    ptr = token;
    result = expanded;
    in_single_quote = 0;
    in_double_quote = 0;
    while (*ptr)
    {   
        // Handle quote state transitions
        if (*ptr == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            ptr++;  // Skip the quote
            continue;
        }
        else if (*ptr == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            ptr++;  // Skip the quote
            continue;
        }
        if (*ptr == '$' && !in_single_quote)
        {
            handle_dollar(&ptr, &result, data, in_single_quote);
            continue ;
        }
        *result++ = *ptr++;
    }
    *result = '\0';
}
