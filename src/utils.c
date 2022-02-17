/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:33:54 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/02/17 13:36:34 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_msg(char *str)
{
	ft_putstr_fd(str, 1);
	return (1);
}

char	*strtolow(char *str)
{
	char *tmp;
	int i;

	i = -1;

	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[++i])
		tmp[i] = (char)ft_tolower(str[i]);
	return (tmp);
}
