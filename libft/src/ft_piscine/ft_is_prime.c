/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:33:09 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:58:25 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_is_prime(int nb)
{
	long	div;

	div = 2;
	if (nb < 2)
		return (0);
	if (nb == 2 || nb == 3)
		return (1);
	while (div * div <= nb)
	{
		if (nb % div == 0)
			return (0);
		div++;
	}
	return (1);
}
