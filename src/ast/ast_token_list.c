#include <minishell.h>

static t_ast	*token_list1(t_ast **ast)
{
	char	*name;

	name = NULL;
	if (!(*ast)->data)
	{
		astree_set_data(*ast, name);
		token_list(ast);
		return (*ast);
	}
	return (NULL);
}

t_ast	*token_list(t_ast **ast)
{
	t_ast	*new_node;

	new_node = token_list1(ast);
	if (new_node)
		return (new_node);
	return (NULL);
}
