/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:36:48 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:00:00 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_string(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	if (ft_putstr(str) == -1)
		return (-1);
	return (ft_strlen(str));
}
