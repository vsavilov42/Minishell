#include <minishell.h>

static t_ast	*and_or6(void)
{
	t_ast	*save;
	t_ast	*result;

	if (!ast_valid_char(NULL, TOK_LPRTH))
		return (NULL);
	save = *g_sh.astree;
	result = cmd_line();
	*g_sh.astree = save;
	if (!result)
		return (NULL);
	if (!ast_valid_char(NULL, TOK_RPRTH))
	{
		astree_del_node(result);
		return (NULL);
	}
	astree_add_and_or(g_sh.astree, result, TRUE);
	return (result);
}

static t_ast	*and_or5(void)
{
	t_ast	*cmd_line_node;
	t_ast	*save;
	t_ast	*result;

	if (!ast_valid_char(NULL, TOK_LPRTH))
		return (NULL);
	save = *g_sh.astree;
	cmd_line_node = cmd_line();
	*g_sh.astree = save;
	if (!cmd_line_node)
		return (NULL);
	if (!ast_valid_char(NULL, TOK_RPRTH)
		|| !ast_valid_char(NULL, TOK_PIPE)
		|| !ast_valid_char(NULL, TOK_PIPE))
	{
		astree_del_node(cmd_line_node);
		return (NULL);
	}
	result = and_or_node(NODE_OR, cmd_line_node);
	if (!and_or())
		return (NULL);
	return (result);
}

t_ast	*and_or_node(int type, t_ast *cmd_line_node)
{
	t_ast	*result;

	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, type);
	astree_root_branch(result, cmd_line_node, NULL);
	astree_add_and_or(g_sh.astree, result, FALSE);
	return (result);
}

t_ast	*hate_norm_and_or(t_token *save)
{
	t_ast	*new_node;

	g_sh.tok = save;
	new_node = and_or5();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = and_or6();
	if (new_node)
		return (new_node);
	return (NULL);
}
