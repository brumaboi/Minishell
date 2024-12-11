/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_exp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:28:35 by marvin            #+#    #+#             */
/*   Updated: 2024/12/07 01:28:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	add_oldpwd_exp(t_var **exp)
{
	t_var	*ptr;
	t_var	*tmp;
	char	*oldpwd;

	if (*exp)
	{
		ptr = *exp;
		while (ptr->next)
		{
			if (!ft_strncmp(ptr->name, "OLDPWD", 6))
				return ;
			ptr = ptr->next;
		}
		oldpwd = ft_strdup("OLDPWD");
		tmp = p_lstnew(oldpwd, NULL);
		if (!oldpwd || !tmp)
		{
			free_env_vars(*exp);
			*exp = NULL;
			return ;
		}
		p_lstadd_back(exp, tmp);
	}
}

void	swap_swap(t_var *ptr)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = ptr->name;
	ptr->name = ptr->next->name;
	ptr->next->name = tmp_name;
	tmp_value = ptr->value;
	ptr->value = ptr->next->value;
	ptr->next->value = tmp_value;
}

void	sort_exp(t_var **export)
{
	int		swapped;
	t_var	*last_sorted;
	t_var	*ptr;

	last_sorted = NULL;
	if (*export == NULL)
		return ;
	swapped = 1;
	while (swapped == 1)
	{
		swapped = 0;
		ptr = *export;
		while (ptr->next != last_sorted)
		{
			if (ptr->name && ptr->next->name
				&& ft_strncmp(ptr->name, ptr->next->name,
					ft_strlen(ptr->name)) > 0)
			{
				swap_swap(ptr);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last_sorted = ptr;
	}
}
