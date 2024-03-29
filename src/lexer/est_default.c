/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   est_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:42:07 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/03 20:42:09 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	tok_est_spc_tab(t_lextype *lt, int l_sz)
{
	if (lt->i > 0)
	{
		lt->tok->name[lt->i] = 0;
		lt->tok->next = (t_token *)malloc(sizeof(t_token));
		if (!lt->tok->next)
			perror_ret("malloc", 1);
		lt->tok = lt->tok->next;
		if (init_tok(lt->tok, l_sz - lt->j))
			return (TRUE);
		lt->i = 0;
	}
	return (FALSE);
}

static void	tok_est_escseq(t_lextype *lt)
{
	char	*tmp;

	tmp = g_sh.line;
	lt->tok->name[lt->i++] = tmp[++lt->j];
	lt->tok->type = TOK_DEFAULT;
}

static int	tok_est_esp_char(t_lextype *lt, int l_sz)
{
	if (lt->i > 0)
	{
		lt->tok->name[lt->i] = '\0';
		lt->tok->next = (t_token *)malloc(sizeof(t_token));
		lt->tok = lt->tok->next;
		if (init_tok(lt->tok, l_sz - lt->j))
			return (1);
		lt->i = 0;
	}
	lt->tok->name[0] = lt->type;
	lt->tok->name[1] = '\0';
	lt->tok->type = lt->type;
	lt->tok->next = (t_token *)malloc(sizeof(t_token));
	lt->tok = lt->tok->next;
	if (init_tok(lt->tok, l_sz - lt->j))
		return (1);
	return (FALSE);
}

int	handle_dflt(t_lextype *lt, int l_sz)
{
	if (lt->type == TOK_QUOTE || lt->type == TOK_DQUOTE
		|| lt->type == TOK_LPBRK)
		tok_est_quotes(lt);
	else if (lt->type == TOK_ESCSEQ)
		tok_est_escseq(lt);
	else if (lt->type == TOK_DEFAULT)
	{
		lt->tok->name[lt->i++] = lt->c;
		lt->tok->type = TOK_DEFAULT;
	}
	else if (lt->type == TOK_SPACE || lt->type == TOK_TAB)
	{
		if (tok_est_spc_tab(lt, l_sz))
			return (TRUE);
	}
	else if (lt->type == TOK_LESS || lt->type == TOK_GREAT
		|| lt->type == TOK_PIPE || lt->type == TOK_SC
		|| lt->type == TOK_LPRTH || lt->type == TOK_RPRTH
		|| lt->type == TOK_AMPER)
		if (tok_est_esp_char(lt, l_sz))
			return (TRUE);
	return (FALSE);
}
