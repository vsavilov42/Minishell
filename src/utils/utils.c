/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:33:54 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/03 20:39:07 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bad_str(char *str)
{
	if (*str == '_' || (*str >= 'A' && *str <= 'Z')
		|| (*str >= 'a' && *str <= 'z'))
		return (0);
	ft_putstr_fd("ShiTTYsh: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" not an invalid identifier\n", 2);
	return (1);
}

int	error_msg(char *str)
{
	ft_putstr_fd(str, 1);
	return (1);
}

int	same_strcmp(char *str1, char *str2)
{
	if (!ft_strncmp(str1, str2, ft_strlen(str1))
		&& ft_strlen(str1) == ft_strlen(str2))
		return (0);
	return (1);
}

char	*strtolow(char *str)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (str[++i])
		tmp[i] = (char)ft_tolower(str[i]);
	return (tmp);
}

int	strlen_env(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}
