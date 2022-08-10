/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:36:16 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/08/10 21:50:20 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_oldpwd(void);
static void	cd_home(void);
static void	cd_last(void);
static void	cd_fromhome(char *arg);

static void	ft_oldpwd(void)
{
	t_envlst	*lst;
	char		*oldpwd;
	char		*tmp;

	oldpwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	lst = *g_sh.env;
	while (lst)
	{
		if (!same_strcmp("OLDPWD", lst->name))
		{
			if (getcwd(oldpwd, PATH_MAX))
			{
				free(lst->value);
				lst->value = oldpwd;
			}
			return ;
		}
		lst = lst->next;
	}
	tmp = ft_strjoin("OLDPWD=", (getcwd(oldpwd, PATH_MAX)));
	envlst_add_back(g_sh.env, new_envlst(tmp));
	free(oldpwd);
	free(tmp);
}

static void	cd_home(void)
{
	t_envlst	*lst;
	char		*home;

	lst = *g_sh.env;
	home = NULL;
	while (lst)
	{
		if (!same_strcmp("HOME", lst->name))
			home = lst->value;
		lst = lst->next;
	}
	if (chdir(home))
		write(2, "ShiTTYsh: cd: HOME not set\n", 27);
}

static void	cd_last(void)
{
	t_envlst	*lst;

	lst = *g_sh.env;
	while (lst)
	{
		if (!same_strcmp("OLDPWD", lst->name))
		{
			if (chdir(lst->value))
				write(2, "ShiTTYsh: cd: OLDPWD not set\n", 29);
			return ;
		}
		lst = lst->next;
	}
	write(2, "ShiTTYsh: cd: OLDPWD not set\n", 29);
}

void	cd_fromhome(char *arg)
{
	char		*tmp;
	char		*dir;
	t_envlst	*lst;

	tmp = NULL;
	lst = *g_sh.env;
	if (!same_strcmp(arg, "~"))
		cd_home();
	else
	{
		tmp = ft_substr(arg, 1, ft_strlen(arg));
		while (lst)
		{
			if (!same_strcmp("HOME", lst->name))
				dir = ft_strjoin(lst->value, tmp);
			lst = lst->next;
		}
		if (chdir(dir))
		{
			write(2, "ShiTTYsh: cd: ", 14);
			write(2, arg, ft_strlen(arg));
			write(2, ": No such file or directory\n", 28);
		}
		free(tmp);
	}
}

int	ft_cd(char **arg)
{
	ft_oldpwd();
	if (!arg[1])
		cd_home();
	else if (arg[1] && chdir(arg[1]) && same_strcmp("-", arg[1])
		&& ft_strncmp("~", arg[1], 1))
	{
		write(2, "ShiTTYsh: cd: ", 14);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": No such file or directory\n", 28);
	}
	else if (!same_strcmp(arg[1], "-"))
		cd_last();
	else if (!ft_strncmp(arg[1], "~", 1))
		cd_fromhome(arg[1]);
	update_pwd();
	return (1);
}
