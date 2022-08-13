#include <minishell.h>

static int	tok_est_spc_tab(t_lextype *lt, int l_sz)
{
	if (lt->i > 0)
	{
		lt->tok->name[lt->i] = '\0';
		lt->tok->next = (t_token *)malloc(sizeof(t_token));
		lt->tok = lt->tok->next;
		init_tok(lt->tok, l_sz + lt->j);
		lt->i = 0;
	}
	lt->tok->name[0] = lt->type;
	lt->tok->name[1] = '\0';
	lt->tok->type = lt->type;
	lt->tok->next = (t_token *)malloc(sizeof(t_token));
	lt->tok = lt->tok->next;
	init_tok(lt->tok, l_sz + lt->j);
	return (0);
}

static void	tok_est_escseq(t_lextype *lt)
{
	char	*tmp;

	tmp = g_sh.line;
	lt->tok->name[lt->i++] = tmp[++lt->j];
	lt->tok->type = TOK_DEFAULT;
}

int	handle_dflt(t_lextype *lt, int l_sz)
{
	if (lt->type == TOK_QUOTE || lt->type == TOK_DQUOTE
		|| lt->type == TOK_LPBRK)
		tok_est_quotes(lt);
	else if (lt->type == TOK_SPACE)
		tok_est_escseq(lt);
	else if (lt->type == TOK_DEFAULT)
	{
		lt->tok->name[lt->i++] = lt->c;
		lt->tok->type = TOK_DEFAULT;
	}
	else if (lt->type == TOK_SPACE || lt->type == TOK_TAB)
	{
		if (tok_est_spc_tab(lt, l_sz))
			return (TRUE);
	}
	return (FALSE);
}
