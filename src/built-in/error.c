/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:41:00 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/22 21:41:01 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_command(char **cmd)
{
	char	*tmp;

	tmp = ft_strjoin("ShiTTYsh: command not found: ", *cmd);
	error_msg(tmp);
	write(1, "\n", 1);
	free(tmp);
	return (0);
}
