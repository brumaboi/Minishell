/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:35:51 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:59:35 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_percent_char(va_list args, const char *format)
{
	char	c;

	if (*format == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		return (1);
	}
	else if (*format == 'c')
	{
		c = va_arg(args, int);
		if (write (1, &c, 1) == -1)
			return (-1);
		return (1);
	}
	return (0);
}
