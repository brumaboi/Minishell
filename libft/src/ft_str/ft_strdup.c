/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:02:52 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/16 12:08:32 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*dup_strcpy(char *dest, const char *src)
{
	int	length;

	length = 0;
	while (src[length] != '\0')
	{
		dest[length] = src[length];
		length++;
	}
	dest[length] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	char			*dup;

	i = 0;
	while (s1[i] != '\0')
		i++;
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	dup_strcpy(dup, s1);
	return (dup);
}
