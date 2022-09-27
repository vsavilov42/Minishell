#include <minishell.h>

static t_ast	*job1(void)
{
	t_ast	*job_node;
	t_ast	*cmd_node;
	t_ast	*result;

	cmd_node = simple_cmd();
	if (!cmd_node)
		return (NULL);
	job_node = job();
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_PIPE);
	astree_root_branch(result, cmd_node, job_node);
	return (result);
}

t_ast	*job(void)
{
	t_ast	*new_node;

	new_node = job1();
	if (new_node)
		return (new_node);
	return (NULL);
}
