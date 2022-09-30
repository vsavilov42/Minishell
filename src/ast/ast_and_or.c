#include <minishell.h>

static t_ast	*and_or4()
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
		|| !ast_valid_char(NULL, TOK_AMPER))
	{
		astree_del_node(cmd_line_node);
		return (NULL);
	}
	result = and_or_node(NODE_AND, cmd_line_node);
	if (!and_or())
		return (NULL);
	return (result);
}

static t_ast	*and_or3()
{
	t_ast	*result;

	result = job();
	if (!result)
		return (NULL);
	astree_add_and_or(g_sh.astree, result, 1);
	return (result);
}

static t_ast	*and_or2()
{
	t_ast	*job_node;
	t_ast	*result;

	job_node = job();
	if (!job_node)
		return (NULL);
	if (!ast_valid_char(NULL, TOK_PIPE))
	{
		astree_del_node(job_node);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_OR);
	astree_root_branch(result, job_node, NULL);
	astree_add_and_or(g_sh.astree, result, FALSE);
	if (!and_or())
		return (NULL);
	return (result);
}

static t_ast	*and_or1()
{
	t_ast	*job_node;
	t_ast	*result;

	job_node = job();
	if (!job_node)
		return (NULL);
	if (!ast_valid_char(NULL, TOK_AMPER))
	{
		astree_del_node(job_node);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_AND);
	astree_root_branch(result, job_node, NULL);
	astree_add_and_or(g_sh.astree, result, FALSE);
	if (!and_or())
		return (NULL);
	return (result);
}

t_ast	*and_or(void)
{
	t_token	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = and_or1();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = and_or2();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = and_or3();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = and_or4();
	if (new_node)
		return (new_node);
	return (hate_norm_and_or(save));
}
