/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:46:41 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/03 20:59:54 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	minmax_status(int num);
static void	exit_iterator(char **arg, int i, int status);

static int	minmax_status(int num)
{
	int	n;
	int	neg;

	n = 0;
	neg = 1;
	if (num < 0)
	{
		neg = -1;
		num = neg * num;
	}
	if (neg == 1)
		while (num-- != 0)
			if (n++ == 255)
				n = 0;
	if (neg == -1)
	{
		n = 256;
		while (num-- != 0)
			if (n-- == 0)
				n = 255;
	}
	return (n);
}

static void	exit_iterator(char **arg, int i, int status)
{
	while (arg[1][++i])
	{
		if (arg[1][0] != '+' && arg[1][0] != '-' && !ft_isdigit(arg[1][i]))
		{
			free_all();
			exit(255);
		}
	}
	status = ft_atoi(arg[1]);
	if (status > 255 || status < 0)
		g_sh.status = minmax_status(status);
	else
		g_sh.status = status;
}

int	ft_exit(char **arg)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	if (!arg[1])
		g_sh.status = 0;
	else
		exit_iterator(arg, i, status);
	write(1, "exit\n", 5);
	free_all();
	exit(g_sh.status);
	return (1);
}
