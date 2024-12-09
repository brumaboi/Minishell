/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:09:06 by sbruma            #+#    #+#             */
/*   Updated: 2024/12/09 20:00:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	skip_whitespace_and_sign(const char **str)
{
	int	sign;

	sign = 1;
	while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\r'
		|| **str == '\f' || **str == '\v')
	{
		(*str)++;
	}
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

static long	check_overflow(long result, int digit, int sign)
{
	if (result > LONG_MAX / 10)
	{
		if (sign == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
	}
	if (result == LONG_MAX / 10)
	{
		if (digit > LONG_MAX % 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
	}
	return (0);
}

static long	convert_str_to_long(const char *str, int sign)
{
	long	result;
	long	overflow_check;
	int		digit;

	result = 0;
	digit = *str - '0';
	while ((unsigned char)(*str) >= '0' && (unsigned char)(*str) <= '9')
	{
		overflow_check = check_overflow(result, digit, sign);
		if (overflow_check != 0)
			return (overflow_check);
		result = 10 * result + digit;
		str++;
	}
	return (sign * result);
}

long	ft_atol(const char *str)
{
	int	sign;

	sign = skip_whitespace_and_sign(&str);
	return (convert_str_to_long(str, sign));
}
