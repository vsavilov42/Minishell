/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:31:11 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/21 20:31:12 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_all(void)
{
	envlst_clear(g_sh.env, free);
	free(g_sh.line);
	free(g_sh.exec);
	free_split(g_sh.cmd->argv);
	free(g_sh.cmd->type_arr);
	free(g_sh.cmd);
	free(g_sh.env);
}
