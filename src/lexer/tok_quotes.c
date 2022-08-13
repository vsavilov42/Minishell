#include <minishell.h>

void	tok_est_quotes(t_lextype *lt)
{
	if (lt->type == TOK_QUOTE)
	{
		lt->ste = STE_QUOTE;
		lt->tok->name[lt->i++] = TOK_QUOTE;
		lt->tok->type = TOK_DEFAULT;
	}
	else if (lt->type == TOK_DQUOTE)
	{
		lt->ste = STE_DQUOTE;
		lt->tok->name[lt->i++] = TOK_DQUOTE;
		lt->tok->type = TOK_DEFAULT;
	}
	else if (lt->type == TOK_LPBRK)
	{
		lt->ste = STE_PBRK;
		lt->tok->name[lt->i++] = TOK_LPBRK;
		lt->tok->type = TOK_DEFAULT;
	}
}
