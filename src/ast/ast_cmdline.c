/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmdline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:54:42 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/03 20:54:44 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_ast	*cmd_line3(void)
{
	t_ast	*and_or_node;

	*g_sh.astree = NULL;
	and_or();
	and_or_node = *g_sh.astree;
	if (!and_or_node)
		return (NULL);
	return (and_or_node);
}

static t_ast	*cmd_line2(void)
{
	t_ast	*and_or_node;
	t_ast	*result;

	*g_sh.astree = NULL;
	and_or();
	and_or_node = *g_sh.astree;
	if (!and_or_node)
		return (NULL);
	if (!ast_valid_char(NULL, TOK_SC))
	{
		astree_del_node(and_or_node);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_SEQ);
	astree_root_branch(result, and_or_node, NULL);
	return (result);
}

static t_ast	*cmd_line1(void)
{
	t_ast	*and_or_node;
	t_ast	*cmd_line_node;
	t_ast	*result;

	*g_sh.astree = NULL;
	and_or();
	and_or_node = *g_sh.astree;
	if (!and_or_node)
		return (NULL);
	if (!ast_valid_char(NULL, TOK_SC))
	{
		astree_del_node(and_or_node);
		return (NULL);
	}
	cmd_line_node = cmd_line();
	if (!cmd_line_node)
	{
		astree_del_node(and_or_node);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_SEQ);
	astree_root_branch(result, and_or_node, cmd_line_node);
	return (result);
}

t_ast	*cmd_line(void)
{
	t_token	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = cmd_line1();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_line2();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_line3();
	if (new_node)
		return (new_node);
	return (NULL);
}
