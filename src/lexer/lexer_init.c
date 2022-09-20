#include <minishell.h>

int	init_tok(t_token *token, int l_sz)
{
	token->name = (char *)malloc(sizeof(char) * (l_sz + 2));
	if (!token->name)
		return (perror_ret("malloc", 1));
	*token->name = '\0';
	token->type = TOK_NULL;
	token->next = NULL;
	return (0);
}

int	init_lt(t_lextype *lt, int l_sz, t_lexer *lex)
{
	lex->tok_lst = (t_token *)malloc(sizeof(t_token));
	if (!lex->tok_lst)
		return (perror_ret("fatal error", 1));
	lt->tok = lex->tok_lst;
	init_tok(lt->tok, l_sz);
	lt->ste = STE_DFLT;
	lt->i = 0;
	lt->j = 0;
	return (FALSE);
}
