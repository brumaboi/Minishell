/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_udecimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:41:05 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:00:04 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_udecimal(va_list args)
{
	char			*str;
	unsigned int	length;

	str = ft_utoa(va_arg(args, unsigned int));
	if (!str)
		return (-1);
	if (ft_putstr(str) == -1)
		return (free(str), -1);
	length = ft_strlen(str);
	free (str);
	return (length);
}
