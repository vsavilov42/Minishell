/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:46:15 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/22 13:50:57 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * DUP_IN_OUT:
 * Esta función realizara un dup de stdin por fin y stdout por fout
 */
int	dup_in_out(int *fin, int *fout)
{
	int	res;

	res = 0;
	if (fin)
		res = dup2(*fin, 0);
	if ((res >= 0) && fout)
		res = dup2(*fout, 1);
	return !(res >= 0);
}

/*
 * 	PIPES_SELECTOR:
 * 	int mode -> describe el tipo de dup2 que debemos usar según que processo llama a la función
 * 		0	->	es un único comando no hace dup
 * 		1	->	lst cmd lee del pipe prev
 * 		2	->	salida o own pipe
 * 		3	->	lectura prev pipe y salida own pipe
 */
void	pipes_selector(int mode, t_exec *own, t_exec *prev, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (mode == 1)
		dup_in_out(&prev->pipe_fd[0], NULL);
	else if (mode == 2)
		dup_in_out(NULL, &own->pipe_fd[1]);
	else if (mode == 3)
		dup_in_out(&prev->pipe_fd[0], &own->pipe_fd[1]);
	while (++i < 2)
	{
		if (prev)
			close(prev->pipe_fd[i]);
		if (own)
			close(own->pipe_fd[i]);
	}
	execute_cmd(cmd);
}
