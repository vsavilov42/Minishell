/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:55:00 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/14 16:13:32 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_ast	*try_redir_out(void)
{
	t_ast	*result;

	result = redir_out();
	if (!result)
		return (NULL);
	astree_root_branch(result, NULL, NULL);
	return (result);
}

static t_ast	*try_redir_in(void)
{
	t_ast	*result;

	result = redir_in();
	if (!result)
		return (NULL);
	astree_root_branch(result, NULL, NULL);
	return (result);
}

t_ast	*redir(void)
{
	t_token	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = try_redir_in();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = try_redir_out();
	if (new_node)
		return (new_node);
	return (NULL);
}
