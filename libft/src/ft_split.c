/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:31:57 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 13:19:24 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	**singleword(char const *s, char c, char **sresult)
{
	int		i;
	size_t	len;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		len = 0;
		while (*s != c && *s && ++s)
			len++;
		sresult[i] = malloc(len + 1);
		if (sresult[i] == NULL)
		{
			while (--i >= 0)
				free(sresult[i]);
			free(sresult);
			return (NULL);
		}
		ft_strlcpy(sresult[i++], s - len, len + 1);
		while (*s == c && *s)
			s++;
	}
	sresult[i] = NULL;
	return (sresult);
}

static int	countword(char const *s, char c)
{
	int	nwords;

	nwords = 0;
	while (*s)
	{
		while (*s != c && *s)
			s++;
		nwords++;
		while (*s == c && *s)
			s++;
	}
	return (nwords);
}

char	**ft_split(char const *s, char c)
{
	size_t	cwords;
	char	**sresult;

	if (s == NULL)
		return (NULL);
	while (*s == c && *s)
		s++;
	cwords = (countword(s, c));
	sresult = (char **)malloc(sizeof(char *) * (cwords + 1));
	if (sresult == NULL)
		return (NULL);
	sresult = singleword(s, c, sresult);
	return (sresult);
}
