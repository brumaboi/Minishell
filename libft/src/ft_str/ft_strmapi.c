/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:38:46 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:01:35 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	length;
	char			*cs;

	length = -1;
	cs = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!cs)
		return (NULL);
	while (s[++length])
		cs[length] = (*f)(length, s[length]);
	cs[length] = '\0';
	return (cs);
}
