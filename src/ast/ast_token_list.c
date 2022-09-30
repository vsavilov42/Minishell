#include <minishell.h>

static t_ast	*token_list1(void)
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

t_ast	*token_list()
{
	t_token	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = token_list1();
	if (new_node)
		return (new_node);
	return (NULL);
}
