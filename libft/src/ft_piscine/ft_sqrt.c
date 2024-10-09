/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:14:08 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:59:20 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_sqrt(int nb)
{
	int		low;
	int		high;
	long	mid;
	long	square;

	low = 1;
	high = nb;
	if (nb == 0)
		return (0);
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		square = mid * mid;
		if (square == nb)
			return (mid);
		else if (square < nb)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (0);
}

// #include <stdio.h>

// int main() {
//     int number;
// 		number = 2147483647;

//     int result = ft_sqrt(number);

//     if (result == 0) {
//         printf("Square root is not an integer for the given number.\n");
//     } else {
//         printf("Square root of %d is: %d\n", number, result);
//     }

//     return 0;
// }