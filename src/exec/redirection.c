/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:46:15 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/22 13:01:23 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * DUP_IN_OUT:
 * Esta función realizara un dup de stdin por fin y stdout por fout
 */
int	dup_in_out(int *fin, int *fout, t_cmd *cmd, t_exec *own, t_exec *prev)
{
	if (fin)
		dup2(*fin, 0);
	if (fout)
		dup2(*fout, 1);
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
	if (mode == 1)
		dup_in_out();
	else if (mode == 2)
		dup_in_out();
	else if (mode == 3)
		dup_in_out();
	if (prev)
	{
		close();
		close();
	}
	if (own)
	{
		close();
		close();
	}
}
