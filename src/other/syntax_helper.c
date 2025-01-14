/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:33:11 by marvin            #+#    #+#             */
/*   Updated: 2025/01/14 20:33:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	many_spaces(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	handle_unmatched_quotes(int in_single_quote, int in_double_quote)
{
	if (in_single_quote || in_double_quote)
	{
		fprintf(stderr, " syntax error: unmatched quote\n");
		return (1);
	}
	return (0);
}
