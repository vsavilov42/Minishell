#ifndef AST_H
# define AST_H

# define AST_LESS "<"
# define AST_DLESS "<<"
# define AST_GREAT ">"
# define AST_DGREAT ">>"
# define AST_PIPE "|"
# define AST_QUOTES "\'"
# define AST_DQUOTES "\""
# define AST_SPACE " "
# define AST_DOLLAR "$"
# define AST_QUEST "?"
# define AST_COMT "#"
# define AST_NULL "\0"

struct s_ast {
	char type;
	char *command;
	void *next;
	void *prev;
};

#endif
