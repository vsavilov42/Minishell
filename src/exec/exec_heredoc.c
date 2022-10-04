#include <minishell.h>

static int	heredoc_job(t_ast *ast)
{
	printf("%p\n", ast);
	return (0);
}

static int	heredoc_cmdline(t_ast *ast)
{
	printf("%p\n", ast);
	return (0);
}

static int	heredoc_and_or(t_ast *ast)
{
	t_nodetype	type;

	type = astree_get_type(ast);
	printf("%d\n", type);
	if (type == NODE_SEQ || type == NODE_AND || type == NODE_OR)
	{
		if (heredoc_and_or(ast->left))
			return (1);
		if (heredoc_and_or(ast->right))
			return (1);
	}
	else
		if (heredoc_job(ast))
			return (1);
	return (0);
}

int	exec_heredoc(t_ast *ast)
{
	if (!ast)
		return (FALSE);
	if (astree_get_type(ast) == NODE_SEQ)
	{
		if (heredoc_and_or(ast->left))
			return (TRUE);
		if (heredoc_cmdline(ast->right))
			return (TRUE);
	}
	else
		if (heredoc_and_or(ast))
			return (TRUE);
	return (FALSE);
}
