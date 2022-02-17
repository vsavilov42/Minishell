/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:18:07 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/02/16 14:11:22 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv)
{
//	char **cmd;
	(void)argv;
/*	cmd = (char **)ft_calloc(1, sizeof(char *) * 3);
	cmd[0] = (char *)ft_calloc(1, sizeof(char) * (ft_strlen("echo") + 1));
	cmd[1] = (char *)ft_calloc(1, sizeof(char) * (ft_strlen("hola") + 1));
	cmd[2] = (char *)ft_calloc(1, sizeof(char) * 1);
	cmd[0] = "eChO";
	cmd[1] = "hola";
	cmd[2] = NULL; */
	if (argc <= 1)
		return(0);
	echo(argv);
	//printf("Hola\n");
	return (0);
}
