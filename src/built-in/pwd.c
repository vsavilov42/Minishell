/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:40:22 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/22 21:40:50 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_pwd(void)
{
	t_envlst	*lst;
	char		*pwd;

	pwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	lst = *g_sh.env;
	while (lst)
	{
		if (!same_strcmp("PWD", lst->name))
		{
			if (getcwd(pwd, PATH_MAX))
				lst->value = ft_strdup(pwd);
		}
		lst = lst->next;
	}
	free(pwd);
}

int	ft_pwd(char **arg)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * PATH_MAX);
	(void)arg;
	if (!pwd)
		return (0);
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		free(pwd);
		return (1);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (1);
}
