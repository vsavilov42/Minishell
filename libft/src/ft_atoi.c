/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 02:45:06 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 18:39:26 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_atoi(const char *str)
{
	int		negative;
	size_t	i;

	i = 0;
	negative = 1;
	while ((*str >= 0x09 && *str <= 0x0d) || (*str == 0x20))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		i = (i * 10) + (*str - '0');
		if (i > 2147483647 && negative == 1)
			return (-1);
		if (i > 2147483648 && negative == -1)
			return (0);
		str++;
	}
	return (negative * i);
}
