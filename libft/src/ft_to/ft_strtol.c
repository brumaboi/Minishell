/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:28:14 by marvin            #+#    #+#             */
/*   Updated: 2024/12/09 19:28:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	skip_whitespace_and_sign(const char **str, int *sign)
{
	*sign = 1;
	while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\r'
		|| **str == '\f' || **str == '\v')
	{
		(*str)++;
	}
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (0);
}

static int	char_to_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

static int	detect_base(const char **str, int base)
{
	if (base == 0)
	{
		if (**str == '0')
		{
			if (*(*str + 1) == 'x' || *(*str + 1) == 'X')
			{
				base = 16;
				*str += 2;
			}
			else
			{
				base = 8;
				(*str)++;
			}
		}
		else
			base = 10;
	}
	return (base);
}

static long	process_conversion(const char **str,
								char **endptr, int base, int sign)
{
	long	result;
	int		digit;

	result = 0;
	while (**str)
	{
		digit = char_to_digit(**str);
		if (digit < 0 || digit >= base)
			break ;
		if (result > (LONG_MAX - digit) / base)
		{
			errno = ERANGE;
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * base + digit;
		(*str)++;
		if (endptr)
			*endptr = (char *)*str;
	}
	return (result);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;

	result = 0;
	if (base < 0 || base == 1 || base > 36)
	{
		if (endptr)
			*endptr = (char *)str;
		return (0);
	}
	skip_whitespace_and_sign(&str, &sign);
	base = detect_base(&str, base);
	if (endptr)
		*endptr = (char *)str;
	result = process_conversion(&str, endptr, base, sign);
	return (sign * result);
}
