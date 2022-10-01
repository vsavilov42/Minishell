#include <minishell.h>

static t_ast	*redir_out2(void)
{
	char	*file;
	t_ast	*result;

	file = NULL;
	if(!ast_valid_char(NULL, TOK_GREAT))
		return (NULL);
	if (!ast_valid_char(&file, TOK_DEFAULT))
	{
		free(file);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_TRUNC);
	astree_set_data(result, file);
	astree_root_branch(result, NULL, NULL);
	return (result);
}

static t_ast	*redir_out1(void)
{
	char	*file;
	t_ast	*result;

	file = NULL;
	if (!ast_valid_char(NULL, TOK_GREAT))
		return (NULL);
	if (!ast_valid_char(NULL, TOK_GREAT))
		return (NULL);
	if (!ast_valid_char(&file, TOK_DEFAULT))
	{
		free(file);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_APPEND);
	astree_set_data(result, file);
	astree_root_branch(result, NULL, NULL);
	return (result);
}

t_ast	*redir_out(void)
{
	t_token	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = redir_out1();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = redir_out2();
	if (new_node)
		return (new_node);
	return (NULL);
}
