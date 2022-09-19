#include <minishell.h>

static int	tok_checker(t_lexer *lex, t_token **tok, t_token *last)
{
//	printf("tok-> %s\n", (*tok)->name);
	if (*tok == NULL)
		return (1);
	if (ft_strlen((*tok)->name) <= 0)
	{
		if (!last)
			lex->tok_lst = (*tok)->next;
		else
			last->next = (*tok)->next;
		free((*tok)->name);
		free(*tok);
		if (!last)
			*tok = lex->tok_lst;
		else
			*tok = last->next;
		return (1);
	}
	return (0);
}

static int	handle_exp(t_lexer *lex, t_tknize *ltype)
{
	int	cnt;

	cnt = 0;
	if (ltype->semaphore == 0 && g_sh.is_exp == FALSE)
	{
		g_sh.is_exp = TRUE;
		g_sh.last = ltype->last;
		cnt = handle_expansion(lex, &ltype->tmp, &ltype->last, ltype);
		g_sh.is_exp = FALSE;
		if (cnt == 1)
			return (-1);
		if (tok_checker(lex, &ltype->tmp, ltype->last))
		{
			g_sh.subtok = TRUE;
			return (1);
		}
	}
	if (ltype->semaphore > 0 && g_sh.is_exp == FALSE)
		ltype->semaphore--;
	if (cnt == -1)
		return (-1);
	else if (cnt == 1)
		return (1);
	return (2);
}

static int	handle_tokdef_token(t_lexer *lex, t_tknize *ltype)
{
	int		cnt;
	char	*trimed;

	if (ltype->heredoc == 0)
	{
		cnt = handle_exp(lex, ltype);
		if (cnt != 2)
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
	return (2);
}

static int	parse_tok(t_lexer *lex, t_tknize *ltype, t_token *tok, t_token *last)
{
	int	sbool;

	*ltype = (t_tknize){0, 0, 0, tok, last};
	while (ltype->tmp)
	{
		if (ltype->tmp->type == TOK_DEFAULT)
		{
			sbool = handle_tokdef_token(lex, ltype);
			if (sbool <= 0)
				return (sbool);
			else if (sbool == 1)
				continue ;
		}
		if (ltype->last && ltype->last->type == TOK_LESS
			&& ltype->tmp->type == TOK_LESS)
			ltype->heredoc = 1;
		else
			ltype->heredoc = 0;
		ltype->last = ltype->tmp;
		ltype->tmp = ltype->tmp->next;
	}
	return (ltype->n_tok);
}

int	manage_tokenize(t_lexer *lex)
{
	t_tknize	*ltype;
	t_token		*tok;
	t_token		*last;
	int		tokens;

	ltype = (t_tknize *)malloc(sizeof(t_tknize));
	if (!ltype)
		return (perror_ret("malloc", 1));
	tok = lex->tok_lst;
	last = NULL;
	tokens = parse_tok(lex, ltype, tok, last);
	return (tokens);
}
