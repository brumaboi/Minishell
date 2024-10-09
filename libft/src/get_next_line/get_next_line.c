/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:49:46 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:02:55 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

static char	*ft_get_line(char *stat)
{
	int		i;
	char	*s;

	i = 0;
	if (!stat[i])
		return (NULL);
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	get_memcpy(s, stat, i);
	s[i] = '\0';
	return (s);
}

static char	*ft_new_stat(char *stat)
{
	char	*newline;
	char	*new_str;

	newline = get_strchr(stat, '\n');
	if (!newline)
		return (free(stat), NULL);
	new_str = (char *)malloc(get_strlen(newline + 1) + 1);
	if (!new_str)
		return (free(stat), free(new_str), NULL);
	get_strcpy(new_str, newline + 1);
	return (free(stat), new_str);
}

static char	*read_str(int fd, char *stat)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;

	read_bytes = 1;
	while (!get_strchr(stat, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(stat), NULL);
		buffer[read_bytes] = '\0';
		stat = get_strjoin(stat, buffer);
	}
	return (stat);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*stat;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stat = read_str(fd, stat);
	if (!stat)
		return (NULL);
	next_line = ft_get_line(stat);
	if (!next_line || next_line[0] == '\0')
	{
		if (stat)
		{
			free(stat);
			stat = NULL;
		}
		return (NULL);
	}
	stat = ft_new_stat(stat);
	return (next_line);
}
