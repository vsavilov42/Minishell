#include <minishell.h>

static t_ast	*job1(void)
{
	t_ast	*job_node;
	t_ast	*cmd_node;
	t_ast	*result;

	cmd_node = simple_cmd();
}

t_ast	*job(void)
{
	t_ast	*new_node;

	new_node = job1();
}
