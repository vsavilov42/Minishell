/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:36:16 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/19 17:11:32 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_oldpwd(void);
static void	cd_home(void);
static void	cd_last(void);

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
				lst->value = oldpwd;
			return ;
		}
		lst = lst->next;
	}
	tmp = ft_strjoin("OLDPWD=", (getcwd(oldpwd, PATH_MAX)));
	envlst_add_back(g_sh.env, new_envlst(tmp));
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
	free(home);
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
			{
				write(2, "ShiTTYsh: cd: OLDPWD not set\n", 29);		
			}
			return ;
		}
		lst = lst->next;
	}
	write(2, "ShiTTYsh: cd: OLDPWD not set\n", 29);		
}

void	update_pwd()
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

int	ft_cd(char **arg)
{
	ft_oldpwd();
	if (arg[1] && chdir(arg[1]) && same_strcmp(arg[1], "-"))
	{
		write(2, "ShiTTYsh: cd: ", 14);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": No such file or directory\n", 28);
	}
	if (!arg[1])
		cd_home();
	if (!same_strcmp(arg[1], "-"))
		cd_last();
	//comprobar si es cd solo
	//sino ver si es - ~
	//- regresa a oldowd
	//sino carpeta origen
	update_pwd();
	return (1);
}
