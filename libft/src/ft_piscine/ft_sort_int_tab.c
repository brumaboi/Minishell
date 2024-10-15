/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:23:24 by sbruma            #+#    #+#             */
/*   Updated: 2024/10/15 22:24:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[j] < tab[i])
			{
				c = tab[i];
				tab[i] = tab[j];
				tab[j] = c;
			}
			j++;
		}
		i++;
	}
}

// #include <stdio.h>
//
// int main()
// {
// 	int tab[]= {7, 6, 5, 3};
// 	ft_sort_int_tab(tab, 4);
// 	printf("%d %d %d %d", tab[0], tab[1], tab[2], tab[3]);
// }
