/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 03:14:34 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 18:02:37 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*a;

	a = 0;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			a = (char *)s;
		++s;
	}
	if (a)
		return (a);
	if (c == '\0')
		return ((char *) s);
	return (0);
}
