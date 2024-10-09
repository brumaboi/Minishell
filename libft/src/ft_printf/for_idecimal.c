/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_idecimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:38:03 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:59:47 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_idecimal(va_list args)
{
	char	*str;
	int		length;

	str = ft_itoa(va_arg(args, int));
	if (!str)
		return (-1);
	if (ft_putstr(str) == -1)
		return (free(str), -1);
	length = ft_strlen(str);
	free (str);
	return (length);
}
