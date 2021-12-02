/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 03:41:27 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 18:00:11 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*des;

	des = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (src < dst)
	{
		dst += len;
		src += len;
		while (len--)
			*(unsigned char *)--dst = *(unsigned char *)--src;
	}
	else
		while (len--)
			*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (des);
}
