/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 05:10:04 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 12:57:22 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*c;

	c = malloc(count * size);
	if (c == NULL)
		return (NULL);
	ft_bzero(c, (count * size));
	return (c);
}
