#include <minishell.h>

void	handle_trim_quotes(char *trim, char *name)
{
	t_trim	e;

	e = (t_trim){-1, 0, ft_strlen(name), 0};
	if (e.len <= 1)
	{
		ft_strcpy(trim, name);
		return ;
	}
	while (++e.i < e.len)
	{
		if ((name[e.i] == TOK_QUOTE || name[e.i] == TOK_DQUOTE)
			&& e.quote == 0)
			e.quote = name[e.i];
		else if (name[e.i] == e.quote)
			e.quote = 0;
		else
			trim[e.j++] = name[e.i];
	}
	trim[e.j] = 0;
}

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
