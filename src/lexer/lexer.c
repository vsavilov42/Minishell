#include <minishell.h>

int	lexer(char *line, int l_sz)
{
	int	n_tok;
	t_lextype	*lt;

	lt = (t_lextype *)malloc(sizeof(t_lextype));
	if (l_sz <= 0 || init_lt(lt, l_sz))
		return (0);
	while (TRUE)
	{
		if (lt->j > l_sz)
			break ;
		lt->c = line[lt->j];
		lt->type = get_lextype(lt->c);
		if (handle_lextype(lt, l_sz))
			return (0);
		lt->j++;
		if (lt->c == '\0')
			break ;
	}
	n_tok = manage_tokenize();
	return (n_tok);
}
