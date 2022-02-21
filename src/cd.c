/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:36:16 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/02/17 21:00:09 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cd(char **arg)
{
	char	*tmp;

	tmp = strtolow(arg[0]);
	if (ft_strncmp(tmp, "cd", 2))
		return(0);
	if (arg[1] != NULL)
		chdir(arg[1]);
	free(tmp);
	return (1);
}
