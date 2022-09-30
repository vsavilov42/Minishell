#include <minishell.h>

static void	print_ast(t_ast *ast)
{
	int	node;
	char	*type;

	if (!ast)
		return ;
	int i = -1;
	while (++i < 6)
		write(1, " ", 1);
	node = astree_get_type(ast);
	if (node & NODE_PIPE)
		type = ft_strdup("|");
	else if (node & NODE_SEQ)
		type = ft_strdup(";");
	else if (node & NODE_REDIR)
		type = ft_strdup("redir");
	else if (node & NODE_RD_IN)
		type = ft_strdup("<");
	else if (node & NODE_HEREDOC)
		type = ft_strdup("<<");
	else if (node & NODE_TRUNC)
		type = ft_strdup(">");
	else if (node & NODE_APPEND)
		type = ft_strdup(">>");
	else if (node & NODE_CMD)
		type = ft_strdup("command");
	else if (node & NODE_ARG)
		type = ft_strdup("argument");
	else
		type = ft_strdup("wtf is that");

	if (ast->type & NODE_DATA)
		printf("Type: [%s], Data: [%s]\n", type, ast->data);
	else
		printf("Type: [%s]\n", type);
	free(type);
	print_ast(ast->left);
}

void	create_tree(t_ast **ast, t_lexer *lex)
{
	g_sh.tok = lex->tok_lst;
	*ast = cmd_line(); // create every case
	print_ast(*ast);
}