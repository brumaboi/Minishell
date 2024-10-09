/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:49:40 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:02:44 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

size_t	get_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*get_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

void	*get_memcpy(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;
	size_t		i;

	i = 0;
	cdest = (char *)dest;
	csrc = (const char *)src;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}

char	*get_strjoin(char *stat, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!stat)
	{
		stat = (char *)malloc(1 * sizeof(char));
		if (!stat)
			return (NULL);
		stat[0] = '\0';
	}
	if (!stat || !buffer)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(stat) + ft_strlen(buffer)) + 1));
	if (!str)
		return (free(stat), NULL);
	i = -1;
	j = 0;
	if (stat)
		while (stat[++i] != '\0')
			str[i] = stat[i];
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[ft_strlen(stat) + ft_strlen(buffer)] = '\0';
	return (free(stat), str);
}

char	*get_strcpy(char *dest, char *src)
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
