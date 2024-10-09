/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:39:32 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:59:42 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_hex(va_list args, const char *format)
{
	char	*base;
	char	*str;
	int		length;

	if (*format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	length = 0;
	str = ft_utoa_base(va_arg(args, unsigned int), base);
	if (!str)
		return (-1);
	if (ft_putstr(str) == -1)
		return (free(str), -1);
	length = ft_strlen(str);
	free (str);
	return (length);
}
