#include <minishell.h>

static int	heredoc_command(t_ast *ast)
{
	t_ast	*redir;

	redir = ast->left;
	while (redir)
	{
		if (astree_get_type(redir) & NODE_HEREDOC)
		{
			if (into_heredoc(redir))
				return (TRUE);
		}
		redir = redir->left;
	}
	return (FALSE);
}

static int	heredoc_pipe(t_ast *ast)
{
	t_ast	*job;

	if (heredoc_command(ast->left))
		return (TRUE);
	job = ast->right;
	while (job && (astree_get_type(job) == NODE_PIPE))
	{
		if (heredoc_command(job->left))
			return (TRUE);
		job = job->right;
	}
	if (heredoc_command(job))
		return (TRUE);
	return (FALSE);
}

static int	heredoc_job(t_ast *ast)
{
	if (!ast)
		return (FALSE);
	if (astree_get_type(ast) == NODE_PIPE)
	{
		if (heredoc_pipe(ast))
			return (TRUE);
	}
	else
		if (heredoc_command(ast))
			return (TRUE);
	return (FALSE);
}

static int	heredoc_and_or(t_ast *ast)
{
	t_nodetype	type;

	type = astree_get_type(ast);
	if (type == NODE_SEQ || type == NODE_AND || type == NODE_OR)
	{
		if (heredoc_and_or(ast->left))
			return (TRUE);
		if (heredoc_and_or(ast->right))
			return (TRUE);
	}
	else
		if (heredoc_job(ast))
			return (TRUE);
	return (FALSE);
}

int	exec_heredoc(t_ast *ast)
{
	if (!ast)
		return (FALSE);
	if (astree_get_type(ast) == NODE_SEQ)
	{
		if (heredoc_and_or(ast->left))
			return (TRUE);
		if (exec_heredoc(ast->right))
			return (TRUE);
	}
	else
		if (heredoc_and_or(ast))
			return (TRUE);
	return (FALSE);
}
