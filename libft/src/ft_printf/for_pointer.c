/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:41:36 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:59:54 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_pointer(va_list args)
{
	unsigned long	number;
	char			*str;
	int				length;

	number = (unsigned long)va_arg(args, void *);
	if (number == 0)
	{
		if (write (1, "0x0", 3) == -1)
			return (-1);
		return (3);
	}
	str = ft_utoa_base(number, "0123456789abcdef");
	if (!str)
		return (-1);
	if (ft_putstr("0x") == -1)
		return (free(str), -1);
	if (ft_putstr(str) == -1)
		return (free(str), -1);
	length = ft_strlen(str);
	free (str);
	return (length + 2);
}
