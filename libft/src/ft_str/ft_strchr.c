/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:15:04 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:00:55 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0' && s[length] != (char)c)
		length++;
	if (s[length] == (char)c)
		return ((char *)&s[length]);
	return (NULL);
}
