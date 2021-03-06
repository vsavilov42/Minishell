/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:59:59 by nortolan          #+#    #+#             */
/*   Updated: 2022/05/24 20:33:45 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	leaks(void)
{
	system("leaks -q minishell");
}*/
/*	atexit(leaks);*/

t_sh	g_sh;

int	main(void)
{
	char	*line;

	init_minishell();
	while (1)
	{
		line = readline("ShiTTYsh: ");
		if (line && *line)
		{
			add_history(line);
			get_lines(line);
		}
		if (line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
