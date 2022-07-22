/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:46:15 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/22 02:37:21 by dexposit         ###   ########.fr       */
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
