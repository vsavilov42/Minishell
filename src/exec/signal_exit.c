/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:18:58 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/08/11 14:19:22 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_status_error_msg_2(int status)
{
	if (status == 141)
		return (ft_strdup("Broken pipe"));
	else if (status == 142)
		return (ft_strdup("Alarm clock"));
	else if (status == 143)
		return (ft_strdup("Terminated"));
	else if (status == 152)
		return (ft_strdup("Cputime limit exceeded"));
	else if (status == 153)
		return (ft_strdup("Filesize limit exceeded"));
	else if (status == 155)
		return (ft_strdup("Profiling timer expired"));
	else if (status == 158)
		return (ft_strdup("Power failure"));
	else if (status == 138)
		return (ft_strdup("User defined signal 1"));
	else if (status == 140)
		return (ft_strdup("User defined signal 2"));
	else if (status == 144)
		return (ft_strdup("Stack fault"));
	return (NULL);
}

static char	*get_status_error_msg(int status)
{
	if (status == 0)
		return (ft_strdup(""));
	else if (status == 1)
		return (ft_strdup(""));
	else if (status == 129)
		return (ft_strdup("Hangup"));
	else if (status == 131)
		return (ft_strdup("Quit"));
	else if (status == 132)
		return (ft_strdup("Illegal instruction"));
	else if (status == 133)
		return (ft_strdup("Trace/BPT trap"));
	else if (status == 134)
		return (ft_strdup("Aborted"));
	else if (status == 136)
		return (ft_strdup("Floating exception"));
	else if (status == 137)
		return (ft_strdup("Killed"));
	else if (status == 135)
		return (ft_strdup("Bus error"));
	else if (status == 139)
		return (ft_strdup("Segmentation fault"));
	else if (status == 159)
		return (ft_strdup("Bad system call"));
	return (get_status_error_msg_2(status));
}

int	status_exit(int status)
{
	int		ext_status;
	char	*error_msg;

	ext_status = (WTERMSIG(status) + 128);
	error_msg = get_status_error_msg(ext_status);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	if (WCOREDUP(status))
		ft_putstr_fd("(core dumped)\n", STDERR_FILENO);
	else
		write(STDERR_FILENO, '\n', 1);
	free(error_msg);
	return (ext_status);
}
