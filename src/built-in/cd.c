/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:36:16 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/03/17 14:02:56 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_cd(char **arg)
{
	char	*tmp;

	tmp = strtolow(arg[0]);
	if (ft_strncmp(tmp, "cd", 2))
		return(0);
	if (arg[1] != NULL)
		if (chdir(arg[1]))
		{
			write(2, "ShiTTYsh: cd: ", 14);
			write(2, arg[1], ft_strlen(arg[1]));
			write(2, ": No such file or directory\n", 28);
		}
	free(tmp);
	return (1);
}
