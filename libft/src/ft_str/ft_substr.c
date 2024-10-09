/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:11:14 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:02:15 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		length;
	size_t		finish;
	char		*cs;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start >= length)
		return (ft_strdup(""));
	finish = length - start;
	if (finish > len)
		finish = len;
	cs = (char *)malloc((finish + 1) * sizeof(char));
	if (!cs)
		return (NULL);
	ft_memcpy (cs, s + start, finish);
	cs[finish] = '\0';
	return (cs);
}
