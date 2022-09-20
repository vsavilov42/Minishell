/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:16:12 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/09/20 17:05:01 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_cmt(char *line)
{
	while (ft_isblank(*line))
		line++;
	if (*line == '#')
		return (1);
	return (0);
}

static int	valid_line(char *line)
{
	if (line == NULL || *line == '\n' || *line == '\0' || is_cmt(line))
		return (1);
	while(*line)
	{
		if (!ft_isblank(*line))
			break ;
		line++;
	}
	return (0);
}

void	get_line(char *line)
{
	int	a_tok;
	t_lexer	lex;

	if (valid_line(line))
		return ;
	a_tok = lexer(line, ft_strlen(line), &lex);
	printf("----> Numero de tokens totales: [%d]\n", a_tok);
	printf("&lex-> %p\n", &lex);
	if (a_tok <= 0)
	{
		printf("entra\n");
		printf("subtok %d\n", g_sh.subtok);
		if (a_tok == FALSE && g_sh.subtok == FALSE)
			perror("error: syntax error\n");
		free_lexer(&lex);
	}
}
