/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:33:54 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/03/23 10:54:57 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bad_str(char *str)
{
	if ((*str >= 0x41 && *str <= 0x5a) || (*str >= 0x61 && *str <= 0x7a))
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
	char *tmp;
	int i;

	i = -1;

	tmp = malloc(sizeof(char) * ft_strlen(str));
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

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
