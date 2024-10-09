/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:00:25 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:57:58 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	length;

	length = 0;
	while (length < n)
	{
		if (((unsigned char *)s)[length] == (unsigned char) c)
			return ((unsigned char *)s + length);
		length++;
	}
	return (NULL);
}
