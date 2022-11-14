/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:43:16 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 12:57:56 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_toklst(t_token **tok, t_token **last,
		t_lexer *lex, t_token *tmp)
{
	int		i;
	t_token	*aux;

	i = 1;
	aux = tmp;
	while (aux->next && ++i)
		aux = aux->next;
	aux->next = (*tok)->next;
	if (lex->tok_lst == *tok)
		lex->tok_lst = tmp;
	else
		(*last)->next = tmp;
	free((*tok)->name);
	free(*tok);
	lex->n_tk += i;
	*tok = aux;
}

static int	close_token(t_lexer *lex, t_token **tok,
		t_token **last, t_tknize *ltype)
{
	t_lexer	tmp;
	t_token	*aux;

	if (ft_strlen((*tok)->name) <= 0)
	{
		ltype->semaphore++;
		return (0);
	}
	else
	{
		if (lexer((*tok)->name, ft_strlen((*tok)->name), &tmp) <= 0)
		{
			free_lexer(&tmp);
			return (1);
		}
	}
	aux = tmp.tok_lst;
	ltype->semaphore = 0;
	while (aux && ++ltype->semaphore)
		aux = aux->next;
	add_toklst(tok, last, lex, tmp.tok_lst);
	return (0);
}

static int	manage_ste(t_token *tok, int *i, int *len, int *ste)
{
	if (*ste == STE_QUOTE)
	{
		if (tok->name[*i] == TOK_QUOTE)
			*ste = STE_DFLT;
	}
	else if (*ste == STE_DQUOTE)
	{
		if (tok->name[*i] == TOK_DOLLAR)
		{
			if (expansion(tok, i, *ste))
				return (1);
			*len = ft_strlen(tok->name);
		}
		else if (tok->name[*i] == TOK_DQUOTE)
			*ste = STE_DFLT;
	}
	return (0);
}

static int	manage_ste_dflt(t_token *tok, int *i, int *len, int *ste)
{
	if (tok->name[*i] == TOK_DOLLAR)
	{
		if (expansion(tok, i, *ste))
			return (1);
		*len = ft_strlen(tok->name);
	}
	else if (tok->name[*i] == TOK_QUOTE)
		*ste = STE_QUOTE;
	else if (tok->name[*i] == TOK_DQUOTE)
		*ste = STE_DQUOTE;
	return (0);
}

int	hdl_exp(t_lexer *lex, t_token **tok, t_token **last, t_tknize *ltype)
{
	int	cnt;
	int	i;
	int	len;
	int	ste;

	i = -1;
	ste = STE_DFLT;
	len = ft_strlen((*tok)->name);
	while (i < len && (*tok)->name[++i] != '\0')
	{
		if (ste == STE_DFLT)
			manage_ste_dflt(*tok, &i, &len, &ste);
		else
			manage_ste(*tok, &i, &len, &ste);
	}
	cnt = close_token(lex, tok, last, ltype);
	return (cnt);
}
