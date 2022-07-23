/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:31:38 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/22 20:15:15 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_cplusic(char *num)
{
	int		i;
	int		n;
	char	*tmp;

	i = -1;
	if (!num)
		return (NULL);
	while (num[++i])
		if (!ft_isdigit(num[i]))
			return ("1");
	n = ft_atoi(num);
	n += 1;
	tmp = ft_itoa(n);
	return (tmp);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
