#include <minishell.h>

void	astree_add_and_or(t_ast **astree, t_ast *ast, int state)
{
	if (!astree || !ast)
		return ;
	if (!*astree)
		*astree = ast;
	else
	{
		if (state == 0)
		{
			(*astree)->right = ast->left;
			ast->left = (*astree);
			*astree = ast;
		}
		else
			(*astree)->right = ast;
	}
}

int	ast_valid_char(char **data, int type)
{
	if (!g_sh.tok)
		return (0);
	if (g_sh.tok->type == type)
	{
		if (data)
		{
			*data = (char *)malloc(sizeof(char) *
				ft_strlen(g_sh.tok->name) + 1);
			if (!*data)
				perror_ret("malloc", 0);
			ft_strcpy(*data, g_sh.tok->name);
		}
		g_sh.tok = g_sh.tok->next;
		return (1);
	}
	g_sh.tok = g_sh.tok->next;
	return (0);
}
