/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:59:59 by nortolan          #+#    #+#             */
/*   Updated: 2022/10/24 18:48:18 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	leaks(void)
{
	system("leaks -q minishell");
}

t_sh	g_sh;

int	main(int argc, char **argv)
{
	char	*line;

	//atexit(leaks);
	init_minishell();
	flags_handle(argc, argv);
	while (1)
	{
		manage_signal();
		line = readline("\033[0;37mShiTTYsh: ");
		if (line && *line)
		{
			add_history(line);
			g_sh.line = line;
			get_line(line);
		}
		if (line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		free(line);
	}
	free(g_sh.env);
	return (EXIT_SUCCESS);
}
