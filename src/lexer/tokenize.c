/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:44:26 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 12:58:46 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	tok_checker(t_lexer *lex, t_token **tok, t_token *last)
{
	if (*tok == NULL)
		return (1);
	if (ft_strlen((*tok)->name) <= 0)
	{
		if (!last)
			lex->tok_lst = (*tok)->next;
		else
			last->next = (*tok)->next;
		free((*tok)->name);
		free(*tok);
		if (!last)
			*tok = lex->tok_lst;
		else
			*tok = last->next;
		return (1);
	}
	return (0);
}

static int	handle_exp(t_lexer *lex, t_tknize *ltype)
{
	int	cnt;

	cnt = 0;
	if (ltype->semaphore == 0 && g_sh.is_exp == FALSE)
	{
		g_sh.is_exp = TRUE;
		g_sh.last = ltype->last;
		cnt = hdl_exp(lex, &ltype->tmp, &ltype->last, ltype);
		g_sh.is_exp = FALSE;
		if (cnt == 1)
			return (-1);
		if (tok_checker(lex, &ltype->tmp, ltype->last))
		{
			g_sh.subtok = TRUE;
			return (1);
		}
	}
	if (ltype->semaphore > 0 && g_sh.is_exp == FALSE)
		ltype->semaphore--;
	if (cnt == -1)
		return (-1);
	else if (cnt == 1)
		return (1);
	return (2);
}

static int	handle_tokdef_token(t_lexer *lex, t_tknize *ltype)
{
	int		cnt;
	char	*trimed;

	if (ltype->heredoc == 0)
	{
		cnt = handle_exp(lex, ltype);
		if (cnt != 2)
			return (cnt);
	}
	if (g_sh.is_exp == FALSE)
	{
		trimed = (char *)malloc(ft_strlen(ltype->tmp->name) + 1);
		handle_trim_quotes(trimed, ltype->tmp->name);
		free(ltype->tmp->name);
		ltype->tmp->name = trimed;
	}
	ltype->n_tok++;
	return (2);
}

static int	parse_tok(t_lexer *lex, t_tknize *ltype)
{
	int	sbool;

	while (ltype->tmp)
	{
		if (ltype->tmp->type == TOK_DEFAULT)
		{
			sbool = handle_tokdef_token(lex, ltype);
			if (sbool <= 0)
				return (sbool);
			else if (sbool == 1)
				continue ;
		}
		if (ltype->last && ltype->last->type == TOK_LESS
			&& ltype->tmp->type == TOK_LESS)
			ltype->heredoc = 1;
		else
			ltype->heredoc = 0;
		ltype->last = ltype->tmp;
		ltype->tmp = ltype->tmp->next;
	}
	return (ltype->n_tok);
}

int	manage_tokenize(t_lexer *lex)
{
	t_tknize	ltype;
	t_token		*tok;
	t_token		*last;
	int			tokens;

	tok = lex->tok_lst;
	last = NULL;
	ltype = (t_tknize){0, 0, 0, tok, last};
	tokens = parse_tok(lex, &ltype);
	return (tokens);
}
