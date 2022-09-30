#include <minishell.h>

static t_ast	*token_list2(void)
{
	t_ast	*result;

	result = redir();
	if (!result)
		return (NULL);
	token_list();
	astree_add_branch(g_sh.command, result, 0);
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

t_ast	*token_list()
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
