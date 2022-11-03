/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:54:17 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/14 16:14:29 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_ast	*token_list4(void)
{
	return (NULL);
}

static t_ast	*token_list3(void)
{
	char	*arg;
	t_ast	*result;

	if (!ast_valid_char(&arg, TOK_DEFAULT))
		return (NULL);
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_ARG);
	astree_set_data(result, arg);
	token_list();
	astree_add_branch(g_sh.command, result, TRUE);
	return (result);
}

static t_ast	*token_list2(void)
{
	t_ast	*result;

	result = redir();
	if (!result)
		return (NULL);
	token_list();
	astree_add_branch(g_sh.command, result, FALSE);
	return (result);
}

static t_ast	*token_list1(void)
{
	char	*name;

	if (!g_sh.command->data)
	{
		if (!ast_valid_char(&name, TOK_DEFAULT))
			return (NULL);
		astree_set_data(g_sh.command, name);
		token_list();
		return (g_sh.command);
	}
	return (NULL);
}

t_ast	*token_list(void)
{
	t_token	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = token_list1();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = token_list2();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = token_list3();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = token_list4();
	if (new_node)
		return (new_node);
	return (NULL);
}
