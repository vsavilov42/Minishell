/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:27:11 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/22 20:44:49 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	verify_echo(char *arg);
static void	write_echo(char **arg, int index, int n);
static void	echo_iterator(char **arg, int i);

static int	verify_echo(char *arg)
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

static void	write_echo(char **arg, int index, int n)
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

static void	echo_iterator(char **arg, int i)
{
	while (arg[i] && ft_strncmp(arg[i], "-n", 2) == 0)
	{
		if (verify_echo(arg[i]) == 0)
			break ;
		i++;
	}
	write_echo(arg, i - 1, 2);
}

int	ft_echo(char **arg)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = strtolow(arg[0]);
	if (!same_strcmp(tmp, "echo"))
	{
		free(tmp);
		if (arg[i] != NULL)
		{
			if (!ft_strncmp(arg[i], "-n", 2) && verify_echo(arg[i]))
			{
				echo_iterator(arg, i);
				return (0);
			}
			else
				write_echo(arg, 0, 1);
			return (0);
		}
		write(1, "\n", 1);
	}
	return (1);
}
