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
	return (SETDATATYPE(ast->type));
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
