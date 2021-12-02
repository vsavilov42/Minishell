/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 03:42:06 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 18:00:04 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t		i;
	char		*des;
	const char	*sour;

	des = dst;
	sour = src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		des[i] = sour[i];
		i++;
	}
	return (dst);
}
