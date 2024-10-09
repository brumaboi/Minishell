/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:19:47 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:01:29 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	length;

	length = -1;
	if (dstsize > 0)
	{
		while (src[++length] && length < (dstsize - 1))
			dst[length] = src[length];
		dst[length] = '\0';
	}
	return (ft_strlen(src));
}
