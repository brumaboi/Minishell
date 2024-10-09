/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:33:54 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:57:40 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static t_list	*map(t_list *lst, void *(*f)(void *), void (*del)(void *),
t_list **new)
{
	t_list	*current;
	void	*tmp;	

	while (lst)
	{
		tmp = f(lst->content);
		if (!tmp)
		{
			ft_lstclear(new, del);
			return (NULL);
		}
		current = ft_lstnew(tmp);
		if (!current)
		{
			del(tmp);
			ft_lstclear(new, del);
			return (NULL);
		}
		ft_lstadd_back(new, current);
		lst = lst->next;
	}
	return (*new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	new = map(lst, f, del, &new);
	if (!new)
		return (NULL);
	return (new);
}
