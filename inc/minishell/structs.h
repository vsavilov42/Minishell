#ifndef STRUCTS_H
# define STRUCTS_H

# include "lexer.h"
# include "astree.h"

typedef struct s_builtin	t_builtin;

//built-in
struct s_builtin
{
	char	*name;
	int	(*f)(char **);
	t_builtin	*next;
};

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
	int		child;
	pid_t		gpid;
	t_builtin	*builtin;
	t_envlst	**env;
	t_token		*tok;
	t_token		*last;
	t_lexer		*lex;
	t_ast		**astree;
	t_ast		*command;
}			t_sh;

extern t_sh	g_sh;

#endif
