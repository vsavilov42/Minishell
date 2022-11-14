/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:13:40 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 10:53:10 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*tmp_from_user(void);
static char	*get_file_name(char *file);
static char	*tmp_from_current(void);


static char	*tmp_from_current(void)
{
	char	*name;
	char	*tmp;

	name = NULL;
	tmp = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	if (getcwd(tmp, PATH_MAX))
	{
		if (access(tmp, R_OK | W_OK) == 0)
			name = get_file_name(tmp);
		free(tmp);
		if (name)
			return (name);
	}
	return (NULL);
}

static char	*tmp_from_user(void)
{
	char	*name;
	char	*tmp;

	name = NULL;
	tmp = return_value("HOME");
	if (tmp)
	{
		if (access(tmp, R_OK | W_OK) == 0)
			name = get_file_name(tmp);
		free(tmp);
		if (name)
			return (name);
	}
	name = tmp_from_current();
	return (name);
}

static char	*get_file_name(char *file)
{
	char	*name;
	char	*tmp;
	int		i;

	i = 0;
	while (++i < 100)
	{
		tmp = ft_itoa(i);
		name = ft_strjoin("/.shtty_", tmp);
		free(tmp);
		tmp = name;
		name = ft_strjoin(file, tmp);
		free(tmp);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
	}
	return (NULL);
}

char	*new_file_name(void)
{
	char	*name;

	name = NULL;
	if (access(EXTERNTMPDIR, R_OK | W_OK) == 0)
	{
		name = get_file_name(EXTERNTMPDIR);
		if (name)
			return (name);
	}
	name = tmp_from_user();
	return (name);
}
