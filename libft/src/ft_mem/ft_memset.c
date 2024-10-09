/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:40:08 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:58:12 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	length;
	char	*cb;

	length = -1;
	cb = b;
	while (++length < len)
		cb[length] = c;
	return (b);
}
