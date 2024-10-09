/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:31:41 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:01:25 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	total_len;

	dst_len = 0;
	src_len = 0;
	total_len = 0;
	while (dst[dst_len] && dst_len < dstsize)
		dst_len++;
	total_len = dst_len + ft_strlen(src);
	if (dst_len < dstsize)
	{
		while (src[src_len] && dst_len + 1 < dstsize)
			dst[dst_len++] = src[src_len++];
		dst[dst_len] = '\0';
	}
	return (total_len);
}
