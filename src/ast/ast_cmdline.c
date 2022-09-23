#include <minishell.h>


static t_ast	*cmd_line1(void)
{
	t_ast	*and_or_node;
	t_ast	*cmd_line_node;
	t_ast	*result;

	and_or();
	and_or_node = *g_sh.astree;
	cmd_line_node = cmd_line();
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_SEQ);
	astree_root_branch(result, and_or_node, cmd_line_node);
	return (result);
}

t_ast	*cmd_line(void)
{
	t_ast	*new_node;

	new_node = cmd_line1();
	if (new_node)
		return (new_node);
	return (NULL);
}
