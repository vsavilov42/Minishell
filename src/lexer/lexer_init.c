#include <minishell.h>

void	init_tok(t_token *token, int l_sz)
{
	token->name = (char *)malloc(sizeof(char *) * (l_sz + 2));
	*token->name = '\0';
	token->type = TOK_NULL;
	token->next = NULL;
}

int	init_lt(t_lextype *lt, int l_sz)
{
	t_lexer	*lex;

	lex = (t_lexer *)malloc(sizeof(t_lexer));
	lex->tok_lst = (t_token *)malloc(sizeof(t_token));
	if (!lex || !lex->tok_lst)
		return (TRUE);
	init_tok(lex->tok_lst, l_sz);
	lt->tok = lex->tok_lst;
	lt->ste = STE_DFLT;
	lt->i = 0;
	lt->j = 0;
	return (FALSE);
}
