/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:18:07 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/03/03 18:50:41 by Vsavilov         ###   ########.fr       */
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

//	atexit(leaks);
	init_minishell();
	while (1)
	{
		line = readline("ShiTTYsh: ");
		tmp = ft_split(line, ' ');
		if (line && *line)
			add_history(line);
		if (tmp[0] != NULL)
		{
		if (!same_strcmp(tmp[0], "echo"))
			echo(tmp);
		if (!same_strcmp(tmp[0], "env"))
			env(tmp);
		if (!same_strcmp(tmp[0], "cd"))
			cd(tmp);
		if (!same_strcmp(tmp[0], "pwd"))
			pwd(tmp);
		if (!same_strcmp(tmp[0], "export"))
			export_env(tmp);
		if (!same_strcmp(tmp[0], "unset"))
			unset(tmp);
		if (!same_strcmp(line, "exit"))
			break ;
		free_split(tmp);
		free(line);
		}
	//	else
	//		error_command(tmp);
	}
	free_split(tmp);
	free(line);
	//printf("Hola\n");
	return (0);
}
