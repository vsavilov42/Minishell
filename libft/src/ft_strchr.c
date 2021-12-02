/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 03:35:21 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 16:19:43 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *s, int c)
{
	char	*sresult;

	if (s == NULL)
		return (NULL);
	sresult = (char *)s;
	while (*sresult != (char)c)
	{
		if (*sresult == '\0')
			return (NULL);
		sresult++;
	}
	return (sresult);
}
