/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:33:19 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:02:40 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static unsigned long	count_digits(unsigned long n)
{
	unsigned long	cn;
	unsigned long	index;

	cn = n;
	index = 0;
	if (n == 0)
		return (1);
	while (cn > 0)
	{
		cn /= 10;
		index++;
	}
	return (index);
}

static char	*convert_to_string(unsigned long n, unsigned long index)
{
	char	*str;

	str = (char *)malloc((index + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[index] = '\0';
	while (index > 0)
	{
		str[--index] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_utoa(unsigned long n)
{
	unsigned long	index;

	index = count_digits(n);
	return (convert_to_string(n, index));
}
