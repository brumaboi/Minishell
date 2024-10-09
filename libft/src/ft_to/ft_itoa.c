/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:33:19 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:02:27 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	index_count(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	minus(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

char	*ft_itoa(int n)
{
	size_t	index;
	char	*result;
	int		is_negative;

	index = index_count(n);
	is_negative = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		is_negative = 1;
	n = minus(n);
	if (is_negative)
		index++;
	result = (char *)malloc((index + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[index] = '\0';
	while (index-- > 0)
	{
		result[index] = n % 10 + '0';
		n /= 10;
	}
	if (is_negative != 0)
		result[0] = '-';
	return (result);
}
