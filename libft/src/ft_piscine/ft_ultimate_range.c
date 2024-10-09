/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:49:12 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:59:28 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_ultimate_range(int **range, int min, int max)
{
	int	*arr;
	int	i;

	if (min >= max)
	{
		range = NULL;
		return (0);
	}
	arr = malloc((max - min) * sizeof(int));
	if (!arr)
		return (-1);
	i = 0;
	while (i < (max - min))
	{
		arr[i] = i + min;
		i++;
	}
	*range = arr;
	return (max - min);
}
