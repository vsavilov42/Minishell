/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:31:21 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/15 14:31:09 by Vsavilov         ###   ########.fr       */
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

static void	init_vars(void)
{
	g_sh.status = 0;
	g_sh.builtin = init_builtin();
	dup2(g_sh.fd_bio[0], STDIN_FILENO);
	dup2(g_sh.fd_bio[1], STDOUT_FILENO);
	g_sh.is_exp = FALSE;
	g_sh.subtok = FALSE;
}

void	init_minishell(void)
{
	get_env();
	init_vars();
	manage_signal();
}
