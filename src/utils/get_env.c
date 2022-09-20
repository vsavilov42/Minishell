/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:31:16 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/09/20 17:23:48 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	start_env(char *shell_lvl, char *pwd)
{
	char	*tmp;

	tmp = NULL;
	if (getcwd(pwd, PATH_MAX))
	{
		tmp = ft_strjoin("PWD=", pwd);
		envlst_add_back(g_sh.env, new_envlst(tmp));
	}
	envlst_add_back(g_sh.env, new_envlst(shell_lvl));
	free(tmp);
}

static void	update_shlvl(void)
{
	t_envlst	*lst;
	char		*tmp;

	lst = *g_sh.env;
	while (lst)
	{
		if (!same_strcmp(lst->name, "SHLVL"))
		{
			tmp = ft_cplusic(lst->value);
			free(lst->value);
			lst->value = tmp;
		}
		lst = lst->next;
	}
}

void	get_env(void)
{
	extern char	**environ;
	int			i;
	char		*pwd;
	char		*shell_lvl;

	i = -1;
	g_sh.env = (t_envlst **)ft_calloc(1, (sizeof(t_envlst *)));
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!g_sh.env || !pwd)
		return ;
	shell_lvl = ft_strdup("SHLVL=1");
	if (*environ)
	{
		while (environ[++i])
			envlst_add_back(g_sh.env, new_envlst(environ[i]));
		update_shlvl();
	}
	else
		start_env(shell_lvl, pwd);
	free(pwd);
	free(shell_lvl);
}
