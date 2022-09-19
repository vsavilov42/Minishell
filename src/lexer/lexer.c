#include <minishell.h>

int	lexer(char *line, int l_sz, t_lexer *lex)
{
	int			n_tok;
	t_lextype	lt;

	lex->n_tk = 0;
	if (g_sh.is_exp == FALSE)
		g_sh.subtok = FALSE;
	if (l_sz <= 0 || init_lt(&lt, l_sz, lex))
		return (0);
	while (TRUE)
	{
		if (lt.j > l_sz)
			break ;
		lt.c = line[lt.j];
		lt.type = get_lextype(lt.c);
		if (handle_lextype(&lt, l_sz))
			return (0);
		lt.j++;
		if (lt.c == TOK_NULL)
			break ;
	}
	n_tok = manage_tokenize(lex);
	if (n_tok == -1)
		return (-1);
	lex->n_tk += n_tok;
	return (lex->n_tk);
}
