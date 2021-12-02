/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:40:10 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 13:14:24 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*newlist;

	newlist = NULL;
	if (lst == NULL || f == NULL)
		return (NULL);
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
		{
			ft_lstclear (&newlist, del);
			lst = lst->next;
		}
		ft_lstadd_back(&newlist, new);
		lst = lst->next;
	}
	new = NULL;
	return (newlist);
}
