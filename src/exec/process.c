/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:00:49 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/20 18:33:39 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
/*
int	wait_process(void)
{
}
*/
