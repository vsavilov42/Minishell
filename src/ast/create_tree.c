#include <minishell.h>

void	create_tree(t_ast **ast, t_lexer *lex)
{
	g_sh.tok = lex->tok_lst;
	*ast = cmd_line1(); // create every case
}
