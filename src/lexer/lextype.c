#include <minishell.h>

static int	get_lextype2(char c)
{
	if (c == ';')
		return (TOK_SC);
	else if (c == '(')
		return (TOK_LPRTH);
	else if (c == ')')
		return (TOK_RPRTH);
	else if (c == '{')
		return (TOK_LPBRK);
	else if (c == '}')
		return (TOK_RPBRK);
	return (TOK_DEFAULT);
}

int	get_lextype(char c)
{
	if (c == '<')
		return (TOK_LESS);
	else if (c == '>')
		return (TOK_GREAT);
	else if (c == '|')
		return (TOK_PIPE);
	else if (c == '\'')
		return (TOK_QUOTE);
	else if (c == '\"')
		return (TOK_DQUOTE);
	else if (c == '\0')
		return (TOK_NULL);
	else if (c == '\n')
		return (TOK_ENDL);
	else if (c == '\t')
		return (TOK_TAB);
	else if (c == ' ')
		return (TOK_SPACE);
	else if (c == '$')
		return (TOK_DOLLAR);
	else if (c == '?')
		return (TOK_QUEST);
	else if (c == '&')
		return (TOK_AMPER);
	return (get_lextype2(c));
}

int	handle_lextype(t_lextype *lt, int l_sz)
{
	if (lt->ste == STE_DFLT)
	{
		if (handle_dflt(lt, l_sz))
			return (TRUE);
	}
	/*else
		handle_ste(lt);
*/	return 1;
}
