/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:59:59 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/21 14:05:25 by nortolan         ###   ########.fr       */
/*   Created: 2022/02/14 12:18:07 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/03/17 15:44:55 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	leaks(void)
{
	system("leaks -q minishell");
}*/
/*	atexit(leaks);*/
t_sh	g_sh;

void	leaks()
{
	system("leaks -q minishell");
}

int	main(void)
{
	char	**tmp;
	char	*line;

//	atexit(leaks);
	init_minishell();
	while (1)
	{
		line = readline("ShiTTYsh: ");
		tmp = ft_split(line, ' ');
		if (line && *line)
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
		builtin(tmp);
		free_split(tmp);
		free(line);
	}
	free_split(tmp);
	free(line);
	return (0);
}
