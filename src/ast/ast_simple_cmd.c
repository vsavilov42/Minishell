#include <minishell.h>

t_ast	*simple_cmd(void)
{
	t_ast	*result;

	result = (t_ast *)malloc(sizeof(t_ast));
	astree_root_branch(result, NULL, NULL);
	astree_set_type(result, NODE_CMD);
	result->data = NULL;
	token_list(&result);
	return (result);
}
