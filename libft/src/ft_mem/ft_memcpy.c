/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:44:41 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:58:04 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	length;

	length = -1;
	if (!dst && !src)
		return (0);
	if (dst != src)
		while (++length < n)
			((unsigned char *)dst)[length] = ((unsigned char *)src)[length];
	return (dst);
}
