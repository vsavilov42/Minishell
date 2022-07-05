/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:23:23 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/05 18:54:11 by dexposit         ###   ########.fr       */
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
	while (aux)
	{
		//create_process(g_sh.cmd);
		printf("%s\n", *(aux->argv));
		aux = aux->next;
	}
	exit(0);
}

void	create_process(t_cmd *cmd, t_exec *prev)
{
	t_exec	*own;

	if (!cmd || !prev)
		return ;
	own = (t_exec *) malloc(sizeof (t_exec *));
	own->pid = fork();
	if (own->pid < 0)
		perror("Fail to do fork\n");
//	builtin(cmd->argv);
}
