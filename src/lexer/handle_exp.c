#include <minishell.h>

static int	close_token(t_token **tok, t_token **last, t_tknize *ltype)
{
	if (ft_strlen((*tok)->name <= 0))
	{
		ltype->semaphore++;
		return (0);
	}
	else
	{
		if (lexer())
	}
}

static int	manage_ste(t_token *tok, int *i, int *len, int *ste)
{
	if (*ste == STE_QUOTE)
	{
		if (tok->name[*i] == TOK_QUOTE)
			*ste = STE_DFLT;
	}
	else if (*ste == STE_DQUOTE)
	{
		if (tok->name[*i] == TOK_DOLLAR)
		{
			if (expansion(tok, i, *ste))
				return (1);
			*len = ft_strlen(tok->name);
		}
		else if (tok->name[*i] == TOK_DQUOTE)
			*ste = STE_DFLT;
	}
	return (0);
}

static int	manage_ste_dflt(t_token *tok, int *i, int *len, int *ste)
{
	if (tok->name[*i] == TOK_DOLLAR)
	{
		if (expansion(tok, i, *ste))
			return (1);
		*len = ft_strlen(tok->name);
	}
	else if (tok->name[*i] == TOK_QUOTE)
		*ste = STE_QUOTE;
	else if (tok->name[*i] == TOK_DQUOTE)
		*ste = STE_DQUOTE;
	return (0);
}

int	handle_expansion(t_token **tok, t_token **last, t_tknize *ltype)
{
	int	cnt;
	int	i;
	int	len;
	int	ste;

	i = -1;
	ste = STE_DFLT;
	len = ft_strlen((*tok)->name);
	while (i < len && (*tok)->name[++i] != '\0')
	{
		if (ste == STE_DFLT)
			manage_ste_dflt(*tok, &i, &len, &ste);
		else
			manage_ste(*tok, &i, &len, &ste);
	}
	cnt = close_token(tok, last, ltype);
	return (cnt);
}
