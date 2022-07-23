/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:42:48 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/22 21:42:49 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(char **arg)
{
	t_envlst	*envlst;

	envlst = *g_sh.env;
	if (arg[1] != NULL)
		return (1);
	while (envlst)
	{
		if (envlst->value)
		{
			ft_putstr_fd(envlst->name, 1);
			write(1, "=", 1);
			ft_putstr_fd(envlst->value, 1);
			write(1, "\n", 1);
		}
		envlst = envlst->next;
	}
	return (0);
}
