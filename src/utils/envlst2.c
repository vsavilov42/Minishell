/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:31:06 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/21 20:31:07 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	envlst_clear(t_envlst **lst, void (*del)(void *))
{
	void	*last;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		del((*lst)->name);
		del((*lst)->value);
		last = *lst;
		*lst = (*lst)->next;
		del(last);
	}
	*lst = NULL;
}
