/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:49:49 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:36:03 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

size_t	get_strlen(const char *s);
char	*get_strchr(char *s, int c);
void	*get_memcpy(void *dest, const void *src, size_t n);
char	*get_strjoin(char *stat, char *buffer);
char	*get_next_line(int fd);
char	*get_strcpy(char *dest, char *src);

#endif