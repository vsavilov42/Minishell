/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:59:59 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/15 11:07:28 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	leaks(void)
{
	system("leaks -q minishell");
}*/
/*	atexit(leaks);*/

int	main(void)
{
	char	*line;

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
