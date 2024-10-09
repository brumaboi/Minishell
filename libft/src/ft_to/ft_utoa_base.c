/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:37:45 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:02:35 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_utoa_base(unsigned long value, char *base)
{
	unsigned long	base_len;
	char			*str;
	unsigned long	tmp;
	int				size;

	base_len = ft_strlen(base);
	tmp = value;
	size = 0;
	if (value == 0)
		size = 1;
	while (tmp)
	{
		tmp /= base_len;
		size++;
	}
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size > 0)
	{
		str[--size] = base[value % base_len];
		value /= base_len;
	}
	return (str);
}
