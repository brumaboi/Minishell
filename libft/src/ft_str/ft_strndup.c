/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:39:36 by sbruma            #+#    #+#             */
/*   Updated: 2024/12/02 21:09:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new_str;

	len = ft_strnlen(s, n);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, s, len);
	new_str[len] = '\0';
	return (new_str);
}
