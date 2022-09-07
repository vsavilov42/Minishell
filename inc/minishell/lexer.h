#ifndef LEXER_H
# define LEXER_H

typedef struct s_token		t_token;
typedef struct s_lexer		t_lexer;
typedef struct s_lextype	t_lextype;
typedef struct s_tknize		t_tknize;
typedef struct s_expand		t_expand;

enum ascii_tk {
	TOK_DEFAULT	= -1,
	TOK_LESS	= '<',
	TOK_GREAT	= '>',
	TOK_PIPE	= '|',
	TOK_QUOTE	= '\'',
	TOK_DQUOTE	= '\"',
	TOK_ESCSEQ	= '\\',
	TOK_NULL	= '\0',
	TOK_ENDL	= '\n',
	TOK_TAB		= '\t',
	TOK_SPACE	= ' ',
	TOK_DOLLAR	= '$',
	TOK_QUEST	= '?',
	TOK_AMPER	= '&',
	TOK_SC		= ';',
	TOK_LPRTH	= '(',
	TOK_RPRTH	= ')',
	TOK_LPBRK	= '{',
	TOK_RPBRK	= '}'
};

enum {
	STE_QUOTE = 0,
	STE_DQUOTE,
	STE_ESC,
	STE_PBRK,
	STE_DFLT
};

struct s_token {
	char	*name;
	int	type;
	t_token	*next;
};

struct s_lexer {
	t_token		*tok_lst;
	int		n_tk;
};

struct	s_lextype {
	t_token	*tok;
	char	c;
	int	type;
	int	ste;
	int	i;
	int	j;
};

struct	s_tknize {
	int	n_tok;
	int	heredoc;
	int	semaphore;
	t_token	*tmp;
	t_token	*last;
};

struct	s_expand {
	int	start;
	int	end;
	int	braket;
	char	*name;
	char	*value;
};

int	lexer(char *line, int l_sz);
int	init_lt(t_lextype *lt, int l_sz);
void	init_tok(t_token *token, int l_sz);
int	get_lextype(char c);
int	handle_lextype(t_lextype *lt, int l_sz);
int	handle_dflt(t_lextype *lt, int l_sz);
void	tok_est_quotes(t_lextype *lt);
int	manage_tokenize(void);
int	handle_expansion(t_token **tok, t_token **last, t_tknize *ltype);
int	expansion(t_token *tok, int *start, int ste);

#endif
