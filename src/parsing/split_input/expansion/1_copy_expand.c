/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:55:42 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 21:55:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

char *expand_env_var(const char *input, t_data *data)
{
    char *var_name;
    char *env_value;
    int var_len;

    if (*input == '?' && *(input + 1) == '\0')
    {
        return ft_itoa(data->exit_status);
    }
    var_len = 0;
    while (input[var_len] && (ft_isalnum(input[var_len]) || input[var_len] == '_'))
        var_len++;
    if (var_len == 0)
        return NULL;
    var_name = ft_strndup(input, var_len);
    if (!var_name)
        return NULL;
    env_value = getenv(var_name);
    free(var_name);
    if (!env_value)
        return ft_strdup(""); // Return an empty string if the variable is not found
    return (ft_strdup(env_value));
}

char *expand_token(const char *token, t_data *data)
{
    char *expanded;
    size_t total_length = 0;

    total_length = get_expansion_len(token, data); //get size
    expanded = malloc(total_length + 1); //allocate memory for said size
    if (!expanded)
        return (NULL);
    fill_expanded(token, expanded, data); //fill the allocated memory
    return (expanded);
}

static char *good_result(char *result, t_data *data, int in_single_quote)
{
    char *expanded_result;

    if (!in_single_quote)
    {
        expanded_result = expand_token(result, data);
        free(result);
        return (expanded_result);
    }
    return (result);
}

char *copy_token(const char *start, const char *end, t_data *data)
{
    char *result;
    int in_single_quote;
    int in_double_quote;
    const char *ptr;

    ptr = start;
    in_single_quote = 0;
    in_double_quote = 0;
    result = malloc((end - start + 1) * sizeof(char));
    if (!result)
        return (NULL);
    while (ptr < end)
    {
        if (quote_state_and_escape(ptr, &in_single_quote, &in_double_quote))
        {
            ptr++;
            result[ptr - start] = *ptr;
            continue ;
        }
        result[ptr - start] = *ptr;
        ptr++;
    }
    result[ptr - start] = '\0';
    return (good_result(result, data, in_single_quote));
}
