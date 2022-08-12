#include <minishell.h>

void	lexer(char *line, int l_sz)
{
	int	i;
	//int	tail;
	t_lextype	*lt;

	i = -1;
	lt = (t_lextype *)malloc(sizeof(t_lextype));
	if (l_sz <= 0 || init_lt(lt, l_sz))
		return ;
	while (++i < l_sz || line[i] != '\0')
	{
		lt->type = get_lextype(line[i]);
	}
}
