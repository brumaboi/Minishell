/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:31:02 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:00:39 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_putstr(char *str)
{
	if (!str)
		return (ft_putstr("(null)"));
	while (*str)
	{
		if (ft_putchar(*str) == -1)
			return (-1);
		str++;
	}
	return (0);
}
