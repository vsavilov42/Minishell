/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:54:41 by vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 13:45:13 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token		t_token;
typedef struct s_lexer		t_lexer;
typedef struct s_lextype	t_lextype;
typedef struct s_tknize		t_tknize;
typedef struct s_expand		t_expand;
typedef struct s_trim		t_trim;

enum e_ascii_tk {
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
	int		type;
	t_token	*next;
};

struct s_lexer {
	t_token		*tok_lst;
	int			n_tk;
};

struct	s_lextype {
	t_token	*tok;
	char	c;
	int		type;
	int		ste;
	int		i;
	int		j;
};

struct	s_tknize {
	int		n_tok;
	int		heredoc;
	int		semaphore;
	t_token	*tmp;
	t_token	*last;
};

struct	s_expand {
	int		start;
	int		end;
	int		braket;
	char	*name;
	char	*value;
};

struct s_trim {
	int		i;
	int		j;
	int		len;
	char	quote;
};

void	tok_est_quotes(t_lextype *lt);
void	handle_trim_quotes(char *trim, char *name);
int		lexer(char *line, int l_sz, t_lexer *lex);
int		init_lt(t_lextype *lt, int l_sz, t_lexer *lex);
int		init_tok(t_token *token, int l_sz);
int		get_lextype(char c);
int		handle_lextype(t_lextype *lt, int l_sz);
int		handle_dflt(t_lextype *lt, int l_sz);
int		manage_tokenize(t_lexer *lex);
int		hdl_exp(t_lexer *lex, t_token **tok, t_token **last, t_tknize *ltype);
int		expansion(t_token *tok, int *start, int ste);

//free functions

void	free_lexer(t_lexer *lex);
void	kill_lex(t_token *tok);

#endif
