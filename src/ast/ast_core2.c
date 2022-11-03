/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_core2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:49:43 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/03 20:49:57 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	astree_add_branch(t_ast *root, t_ast *node, int state)
{
	t_ast	*tmp;

	if (!root || !node)
		return ;
	if (state)
	{
		tmp = root->right;
		root->right = node;
		node->right = tmp;
		node->left = NULL;
	}
	else
	{
		tmp = root->left;
		root->left = node;
		node->left = tmp;
		node->right = NULL;
	}
}
