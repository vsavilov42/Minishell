/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:23:23 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/05 18:09:11 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	To execute the cmds:
 *	1-	create process
 *		- use fork
 *		- use dup2 in infile and outfile
 *		- if there is a pipe repeat with next command
 *		- execute cmd
 *	2-	check and change the infile and outfile
 *	3-	execute
 *			builtin
 *			execve
*/

void	executer(t_parse *cmd)
{
	t_cmd	*aux;

	aux = cmd->head_cmd;
	//aux = cmd;
	while (aux)
	{
		printf("%s\n", *(aux->argv));
		aux = aux->next;
	}
	//create_process(g_sh.cmd);
	exit(0);
}

void	create_process(t_cmd *cmd)
{
	builtin(cmd->argv);
}
