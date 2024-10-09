/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:56:08 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:58:09 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cdst;
	unsigned char	*csrc;

	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		cdst += len - 1;
		csrc += len - 1;
		while (len--)
			*cdst-- = *csrc--;
	}
	else
		while (len--)
			*cdst++ = *csrc++;
	return (dst);
}
