#include <minishell.h>

static t_ast	*and_or1()
{
	t_ast	*job_node;
	t_ast	*result;

	job_node = job();
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_AND);
	astree_root_branch(result, job_node, NULL);
	if (!and_or())
		return (NULL);
	return (result);
}

t_ast	*and_or(void)
{
	t_ast	*new_node;

	new_node = and_or1();
	if (new_node)
		return (new_node);
	return (NULL);
}
