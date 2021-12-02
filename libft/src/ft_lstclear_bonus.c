/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:44:33 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 13:09:00 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	void	*last;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		last = *lst;
		*lst = (*lst)->next;
		free(last);
	}
	*lst = NULL;
}
