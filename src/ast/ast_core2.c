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
