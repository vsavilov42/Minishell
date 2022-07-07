/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:18 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/07 13:41:09 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	new_fork(t_exec *exe)
{
	exe->pid = fork();
	if (exe->pid < 0)
		perror("Fail to execute fork\n");
	return (exe->pid >= 0);
}
