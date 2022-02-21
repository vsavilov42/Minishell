/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:33:54 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/02/19 19:21:35 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_msg(char *str)
{
	ft_putstr_fd(str, 1);
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
