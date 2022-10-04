/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:53:42 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/04 13:34:30 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_ast	*redir_in2(void)
{
	char	*file;
	t_ast	*result;

	file = NULL;
	if (!ast_valid_char(NULL, TOK_LESS))
		return (NULL);
	if (!ast_valid_char(&file, TOK_DEFAULT))
	{
		free(file);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_RD_IN);
	astree_set_data(result, file);
	astree_root_branch(result, NULL, NULL);
	return (result);
}

static t_ast	*redir_in1(void)
{
	char	*file;
	t_ast	*result;

	file = NULL;
	if (!ast_valid_char(NULL, TOK_LESS))
		return (NULL);
	if (!ast_valid_char(NULL, TOK_LESS))
		return (NULL);
	if (!ast_valid_char(&file, TOK_DEFAULT))
	{
		free(file);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_HEREDOC);
	astree_set_data(result, file);
	astree_root_branch(result, NULL, NULL);
	return (result);
}

t_ast	*redir_in(void)
{
	t_token	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = redir_in1();
	if (new_node)
	{
		printf("redir_in1 ");
		return (new_node);
	}
	g_sh.tok = save;
	new_node = redir_in2();
	if (new_node)
	{
		printf("redir_in2 ");
		return (new_node);
	}
	return (NULL);
}
