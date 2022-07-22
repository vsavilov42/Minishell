/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:00:49 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/22 02:15:06 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*last_cmd_exec(t_cmd *cmd)
{
	static t_cmd	**lst=NULL;
	t_cmd			*aux;

	if (cmd)
	aux = g_sh.cmd;
	//aux = g_sh.cmd;
	while (aux && (aux->next != *lst))
		aux = aux->next;
	*lst = aux;
	return (*lst);
}
/*
UNUSED FUNCTIONS TO WAIT PROCESS*/
pid_t	*create_pid_str(t_cmd *cmd)
{
	int		num;
	t_cmd	*aux;
	pid_t	*res;

	num = 0;
	aux = cmd;
	while(aux && (num++ >= 0))
		aux = aux->next;
	printf("número de commandos: %d\n", num);
	res = (pid_t *) malloc(sizeof(pid_t) * num);
	if (!res)
		return(perror("Malloc fail\n"), NULL);
	//res[num] = NULL;
	while (--num >= 0)
		res[num] = 0;
	return (res);
}

void	save_pid(pid_t id)
{
	pid_t	*aux;
	int		i;

	aux = g_sh.pid;
	while (aux && (*aux++ != 0));
	if (aux)
		*aux = id;
	i = -1;
	while (g_sh.pid[++i])
		printf("processo %d, con id-> %d\n", i, g_sh.pid[i]);
}
/*
int	wait_process(void)
{
}
*/
