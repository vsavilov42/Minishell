/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 03:24:34 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 13:22:57 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*sresult;
	unsigned int	i;

	if (s == NULL || *f == NULL)
		return (NULL);
	sresult = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (sresult == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		sresult [i] = f (i, s[i]);
	sresult[i] = '\0';
	return (sresult);
}
