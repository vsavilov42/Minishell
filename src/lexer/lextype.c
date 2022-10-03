/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lextype.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:43:08 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/03 20:43:09 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_lextype2(char c)
{
	if (c == ';')
		return (TOK_SC);
	else if (c == '(')
		return (TOK_LPRTH);
	else if (c == ')')
		return (TOK_RPRTH);
	else if (c == '{')
		return (TOK_LPBRK);
	else if (c == '}')
		return (TOK_RPBRK);
	return (TOK_DEFAULT);
}

int	get_lextype(char c)
{
	if (c == '<')
		return (TOK_LESS);
	else if (c == '>')
		return (TOK_GREAT);
	else if (c == '|')
		return (TOK_PIPE);
	else if (c == '\'')
		return (TOK_QUOTE);
	else if (c == '\"')
		return (TOK_DQUOTE);
	else if (c == '\0')
		return (TOK_NULL);
	else if (c == '\n')
		return (TOK_ENDL);
	else if (c == '\t')
		return (TOK_TAB);
	else if (c == ' ')
		return (TOK_SPACE);
	else if (c == '?')
		return (TOK_QUEST);
	else if (c == '&')
		return (TOK_AMPER);
	return (get_lextype2(c));
}

static void	handle_ste(t_lextype *lt)
{
	if (lt->ste == STE_QUOTE)
	{
		lt->tok->name[lt->i++] = lt->c;
		if (lt->type == TOK_QUOTE)
			lt->ste = TOK_DEFAULT;
	}
	else if (lt->ste == STE_DQUOTE)
	{
		lt->tok->name[lt->i++] = lt->c;
		if (lt->type == TOK_DQUOTE)
			lt->ste = TOK_DEFAULT;
	}
	else if (lt->ste == STE_PBRK)
	{
		lt->tok->name[lt->i++] = lt->c;
		if (lt->type == TOK_RPBRK)
			lt->ste = TOK_DEFAULT;
	}
}

int	handle_lextype(t_lextype *lt, int l_sz)
{
	if (lt->ste == STE_DFLT)
	{
		if (handle_dflt(lt, l_sz))
			return (TRUE);
	}
	else
		handle_ste(lt);
	if (lt->type == TOK_NULL)
	{
		if (lt->i > 0)
		{
			lt->tok->name[lt->i] = '\0';
			lt->i = 0;
		}
	}
	return (0);
}
