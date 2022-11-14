/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:49:31 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 12:49:24 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	astree_root_branch(t_ast *root, t_ast *left, t_ast *right)
{
	if (!root)
		return ;
	root->left = left;
	root->right = right;
}

void	astree_set_type(t_ast *ast, t_nodetype type)
{
	if (!ast)
		return ;
	ast->type = type;
}

int	astree_get_type(t_ast *ast)
{
	return (ast->type & (~(NODE_DATA)));
}

void	astree_set_data(t_ast *ast, char *data)
{
	if (!ast || !data)
		return ;
	ast->data = data;
	ast->type |= NODE_DATA;
}

void	astree_del_node(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type & NODE_DATA)
		free(ast->data);
	astree_del_node(ast->left);
	astree_del_node(ast->right);
	free(ast);
}
