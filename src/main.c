/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:59:59 by nortolan          #+#    #+#             */
/*   Updated: 2022/02/18 11:54:52 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			//printf("%s\n", line);
		}
		if (line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		free(line);
	}
	//printf("Hola\n");
	return (EXIT_SUCCESS);
}
