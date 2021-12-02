/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 03:33:21 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 13:19:55 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;
	size_t	lstr;

	i = -1;
	lstr = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * lstr + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[++i])
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}
