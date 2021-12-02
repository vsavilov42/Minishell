/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 05:06:01 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/21 14:08:15 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	countnum(int n)
{
	int	i;

	i = 1;
	while (n > 9 && i++)
		n = n / 10;
	return (i);
}

char	*ft_itoa(int n)
{
	int		minint;
	int		count;
	char	*sresult;
	int		sign;

	sign = 0;
	minint = 0;
	if (n == -2147483648 && ++minint)
		n = -147483648;
	if (n < 0 && ++sign)
		n *= -1;
	count = countnum(n);
	sresult = ft_calloc(sizeof(char) * count + sign + minint + 1, 1);
	if (sresult == NULL)
		return (NULL);
	if (minint == 1)
		sresult[1] = '2';
	if (sign != 0)
		sresult[0] = '-';
	while (--count >= 0)
	{
		sresult[count + minint + sign] = n % 10 + 0x30;
		n /= 10;
	}
	return (sresult);
}
