/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:18:07 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/02/21 14:22:43 by Vsavilov         ###   ########.fr       */
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
		if (!ft_strncmp(tmp[0], "echo", 4))
			echo(tmp);
		if (!ft_strncmp(tmp[0], "env", 3) && ft_strlen(tmp[0]) == 3)
			env(tmp);
		if (!ft_strncmp(tmp[0], "cd", 2) && ft_strlen(tmp[0]) == 2)
			cd(tmp);
		if (!ft_strncmp(tmp[0], "pwd", 3) && ft_strlen(tmp[0]) == 3)
			pwd(tmp);
		if (!ft_strncmp(tmp[0], "export", 6) && ft_strlen(tmp[0]) == 6)
			export_env(tmp);
		if (!ft_strncmp(line, "exit", 4) && ft_strlen(tmp[0]) == 4)
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
