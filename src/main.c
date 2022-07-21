/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:59:59 by nortolan          #+#    #+#             */
/*   Updated: 2022/07/21 19:46:02 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	leaks(void)
{
	system("leaks -q minishell");
}

t_sh	g_sh;

int	main(void)
{
	char	*line;

	atexit(leaks);
	init_minishell();
	while (1)
	{
		manage_signal();
		line = readline("ShiTTYsh: ");
		if (line && *line)
		{
			add_history(line);
			g_sh.line = line;
			get_lines(line);
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
