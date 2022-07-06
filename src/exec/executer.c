/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:23:23 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/06 15:41:03 by dexposit         ###   ########.fr       */
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
	pid_t	id;
	int		status;

	aux = cmd->head_cmd;
	id = create_process(aux, NULL);
/*	while (aux)
	{
		//create_process(g_sh.cmd);
		printf("%s\n", *(aux->argv));
		aux = aux->next;
	}*/
	waitpid(id, &status, 0);
//	exit(status);
}

pid_t	create_process(t_cmd *cmd, t_exec *prev)
{
	t_exec	*own;

	own = (t_exec *) malloc(sizeof (t_exec *));
	//rellenar structura own
	if (cmd->next)
		own->pid = fork();
	if (own->pid < 0)
		perror("Fail to do fork\n");
	else if (own->pid == 0 && cmd->next)
		create_process(cmd->next, own);
	else if (own->pid == 0 && !cmd->next)
		printf("ultimo hijo: %s\n", *(cmd->argv));
	else if (prev)
		printf("process padre hijo  of the command: %s\n", *(cmd->argv));
	else
		printf("1processo cmd %s\n", *(cmd->argv));
//	if (prev)
//		waitpid(prev->pid, &prev->status, 0);
	return (own->pid);
}

void	initialize_exec_struct(t_cmd *cmd, t_exec *prev)
{
	t_exec	*res;

	if (!prev)
		return ;
	res = (t_exec *) malloc(sizeof(t_exec *));
	if (!res)
		perror("Fail to reserve memory\n");
	if (cmd->next)
		pipe(res->pipe_fd);
}
