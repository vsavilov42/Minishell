/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:18 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/07 18:18:10 by dexposit         ###   ########.fr       */
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

void	modify_in_out_cmd(t_cmd *cmd, t_exec *prev, t_exec *own)
{
	//esta función va a usar dup2 en las redirecciones menos pipes
	//1 para los infiles
	//2 para los outfiles
}
