/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:31:11 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/09/13 21:47:46 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	kill_lex(t_token *tok)
{
	if (tok)
	{
		free(tok->name);
		kill_lex(tok->next);
		free(tok);
	}
}

void	free_lexer(t_lexer *lex)
{
	if (!lex)
		return ;
	kill_lex(lex->tok_lst);
}

void	free_all(void)
{
	envlst_clear(g_sh.env, free);
	free(g_sh.line);
	free(g_sh.env);
}
