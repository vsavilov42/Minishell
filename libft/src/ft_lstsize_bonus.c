/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:38:13 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 13:15:15 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_lstsize(t_list *lst)
{
	size_t	size;

	size = 0;
	if (lst == NULL)
		return (0);
	while (lst && ++size)
		lst = lst->next;
	return (size);
}
