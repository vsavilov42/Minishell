/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:18:07 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/03/08 13:19:14 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_built	g_built;

void	leaks()
{
	system("leaks -q minishell");
}

int	main(void)
{
	char	**tmp;
	char	*line;

	atexit(leaks);
	init_minishell();
	while (1)
	{
		line = readline("ShiTTYsh: ");
		tmp = ft_split(line, ' ');
		if (line && *line)
			add_history(line);
		builtin(tmp);
		free_split(tmp);
		free(line);
	}
	free_split(tmp);
	free(line);
	return (0);
}
