/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 03:30:58 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 13:20:27 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sresult;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	sresult = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (sresult == NULL)
		return (NULL);
	ft_strlcpy (sresult, s1, ft_strlen(s1) + 1);
	ft_strlcat (sresult, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (sresult);
}
