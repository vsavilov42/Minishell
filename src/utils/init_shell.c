/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:31:21 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/08/13 11:56:29 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	flags_handle(int argc, char **argv)
{
	if (argc > 1)
	{
		if (!same_strcmp(argv[1], "-c"))
		{
			if (argc > 3)
			{
				ft_putstr_fd("-c: option requires an argument\n", STDERR_FILENO);
				exit(2);
			}
			else
			{
				get_line(argv[2]);
				exit(g_sh.status);
			}

		}
		else
		{
			ft_putstr_fd("error: no valid argument\n", STDERR_FILENO);
			exit(127);
		}
	}
}

void	init_minishell(void)
{
	get_env();
	manage_signal();
}
