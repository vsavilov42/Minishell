/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:55:39 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 12:38:38 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_tree(t_ast **ast, t_lexer *lex)
{
	g_sh.astree = (t_ast **)malloc(sizeof(t_ast *));
	if (!g_sh.astree)
		ft_putstr_fd("malloc", 1);
	*g_sh.astree = NULL;
	g_sh.tok = lex->tok_lst;
	*ast = cmd_line();
}
