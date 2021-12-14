/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:59:59 by nortolan          #+#    #+#             */
/*   Updated: 2021/12/14 17:51:12 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("test prompt>>> ");
		if (line && *line)
		{
			add_history(line);
			printf("%s\n", line);
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
