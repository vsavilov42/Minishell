#include <minishell.h>

static int	handle_tokdef_token(t_tknize *ltype)
{
	int		cnt;
	char	*trimed;

	if (ltype->heredoc == 0)
	{
		cnt = handle_wc_exp(ltype);
		if (cnt < 0)
			return (cnt);
	}
	if (g_sh.is_exp == FALSE)
	{
		trimed = (char *)malloc(ft_strlen(ltype->tmp->name) + 1);
		handle_trim_quotes(trimed, ltype->tmp->name);
		free(ltype->tmp->name);
		ltype->tmp->name = trimed;
	}
	ltype->n_tok++;
	return (1);
}

static void	parse_tok(t_tknize *ltype, t_token *tok, t_token *last)
{
	int	sbool;

	ltype->n_tok = 0;
	ltype->heredoc = 0;
	ltype->semaphore = 0;
	ltype->tmp = tok;
	ltype->last = last;
	while (ltype->tmp)
	{
		if (ltype->tmp->type == TOK_DEFAULT)
		{
			sbool = handle_tokdef_token(ltype);
			if (sbool <= 0)
				break ;
		}
		if (ltype->last && ltype->last->type == TOK_LESS
			&& ltype->tmp->type == TOK_LESS)
			ltype->heredoc = 1;
		else
			ltype->heredoc = 0;
		ltype->last = ltype->tmp;
		ltype->tmp = ltype->tmp->next;
	}
}

int	manage_tokenize(void)
{
	t_tknize	*ltype;
	t_token		*tok;
	t_token		*last;

	ltype = (t_tknize *)malloc(sizeof(t_tknize));
	if (!ltype)
		return (0);
	tok = g_sh.lex->tok_lst;
	last = NULL;
	parse_tok(ltype, tok, last);
	return (ltype->n_tok);
}
