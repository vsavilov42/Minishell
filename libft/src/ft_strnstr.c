/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 03:15:39 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 13:24:03 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	*x;

	i = 0;
	x = (char *)haystack;
	n_len = ft_strlen(needle);
	if (n_len == 0 || haystack == needle)
		return (x);
	while (x[i] != '\0' && i < len)
	{
		c = 0;
		while (x[i + c] != '\0' && needle[c] != '\0'
			&& x[i + c] == needle[c] && i + c < len)
			c++;
		if (c == n_len)
			return (x + i);
		i++;
	}
	return (0);
}
