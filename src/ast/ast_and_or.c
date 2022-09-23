#include <minishell.h>

static t_ast	*and_or1()
{
	t_ast	*job_node;
	t_ast	*result;

	job_node = job();
}

t_ast	*and_or(void)
{
	t_ast	*new_node;

	new_node = and_or1();
}
