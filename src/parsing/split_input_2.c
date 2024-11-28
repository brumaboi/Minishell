/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:49:10 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 21:49:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
//special_char

int	special_char_len(const char *str)
{
	if (str[0] == '|' || str[0] == '<' || str[0] == '>' || str[0] == '&')
	{
		if (str[0] == str[1])
			return (2);
		return (1);
	}
	return (0);
}

char *process_special_char(const char *str)
{
    char *result;
    int len;

    len = special_char_len(str);
    result = malloc((len + 1) * sizeof(char));
    if (!result)
        return (NULL);
    ft_strncpy(result, str, len);
    result[1] = '\0';
    return (result);
}

int is_special_char(const char *str)
{
    if (*str == '|' || *str == '<' || *str == '>' || *str == ';' || *str == '&' || *str == '(' || *str == ')') 
        return (1);
    if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0
        || ft_strncmp(str, "&&", 2) == 0 || ft_strncmp(str, "||", 2) == 0)
        return (2);
    return (0);
}
