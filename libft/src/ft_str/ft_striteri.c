/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:09:37 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 11:01:18 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	length;

	length = -1;
	while (s[++length] != '\0')
		f(length, &s[length]);
}
