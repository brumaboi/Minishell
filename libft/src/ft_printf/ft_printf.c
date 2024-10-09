/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:12:49 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:00:09 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	handle_format_specifier(const char **fp, va_list args)
{
	int		print_fp;
	char	format;

	print_fp = 0;
	format = **fp;
	if (format == 'c' || format == '%')
		print_fp += ft_print_percent_char(args, *fp);
	else if (format == 's')
		print_fp += ft_print_string(args);
	else if (format == 'p')
		print_fp += ft_print_pointer(args);
	else if (format == 'd' || format == 'i')
		print_fp += ft_print_idecimal(args);
	else if (format == 'u')
		print_fp += ft_print_udecimal(args);
	else if (format == 'x' || format == 'X')
		print_fp += ft_print_hex(args, *fp);
	else
	{
		if (ft_putchar(**fp) == -1)
			return (-1);
		print_fp++;
	}
	(*fp)++;
	return (print_fp);
}

int	ft_printf(const char *fp, ...)
{
	va_list	args;
	int		print_fp;
	int		result;

	print_fp = 0;
	va_start(args, fp);
	while (*fp)
	{
		if (*fp == '%')
		{
			fp++;
			result = handle_format_specifier(&fp, args);
			if (result == -1)
				return (-1);
			print_fp += result;
		}
		else
		{
			if (ft_putchar(*fp) == -1)
				return (-1);
			print_fp++;
			fp++;
		}
	}
	return (va_end(args), print_fp);
}
