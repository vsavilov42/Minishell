#ifndef STRUCTS_H
# define STRUCTS_H

# include "lexer.h"
# include "astree.h"

//built-in
typedef struct s_envlst
{
	char			*name;
	char			*value;
	struct s_envlst	*next;
}			t_envlst;

//global
typedef struct s_sh
{
	int			status;
	char		*line;
	int		fd_bio[2];
	int		is_exp;
	int		subtok;
	t_envlst	**env;
	t_token		*tok;
	t_token		*last;
	t_lexer		*lex;
	t_ast		**astree;
	t_ast		*command;
}			t_sh;

extern t_sh	g_sh;

#endif
