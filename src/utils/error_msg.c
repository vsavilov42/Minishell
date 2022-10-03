/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:38:11 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/03 20:38:11 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	perror_ret(const char *s, int code)
{
	if (!s)
		perror("minishell");
	else
		perror(s);
	return (code);
}

int	error_ret(const char *s, int code)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	return (code);
}
