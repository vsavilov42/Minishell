/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:27:11 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/02/17 11:53:34 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	verify_echo(char *arg)
{
	int	i;

	i = 1;
	if (!ft_strncmp(arg, "-n", 2))
	{
		while (arg[++i])
		{
			if (arg[i] != 'n')
				return (0);
		}
	}
	return (1);
}

void	write_echo(char **arg, int index, int n)
{
	while (arg[++index])
	{
		write(1, arg[index], ft_strlen(arg[index]));
		if (arg[index + 1])
			write(1, " ", 1);
	}
	if (n == 1)
		write(1, "\n", 1);
}

int	echo(char **arg)
{
	int	i;

	i = 2;
	if (!ft_strncmp(strtolow(arg[1]), "echo", 4) && ft_strlen(arg[1]) == 4)
	{
		if (arg[i] != NULL)
		{
			if (!ft_strncmp(arg[i], "-n", 2))
			{
				while (arg[i] && ft_strncmp(arg[i], "-n", 2) == 0)
				{
					if (verify_echo(arg[i]) == 0)
						break ;
					i++;
				}
				write_echo(arg, i - 1, 2);
				return (0);
			}
			else
				write_echo(arg, 1, 1);
			return (0);
		}
		write(1, "\n", 1);
	}
	return (error_msg(ft_strjoin("ShiTTYsh: command not found: ", arg[1])));
}
