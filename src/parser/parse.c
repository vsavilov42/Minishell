/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:16:12 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/11/10 14:00:39 by Vsavilov         ###   ########.fr       */
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
	while (*line)
	{
		if (!ft_isblank(*line))
			break ;
		line++;
	}
	return (0);
}

static int	parser_astree(t_lexer *lex)
{
	t_ast	*ast;

	if (lex->n_tk <= 0)
		return (1);
	create_tree(&ast, lex);
	if (g_sh.tok && g_sh.tok->type != 0)
	{
		ft_putstr_fd("error: sysntax error near: ", STDERR_FILENO);
		return (perror_ret(g_sh.tok->name, 1));
	}
	print_ast(ast, 0);
	if (!exec_heredoc(ast))
		exec_astree(ast);
	astree_del_node(ast);
	return (0);
}

void	get_line(char *line)
{
	int		a_tok;
	t_lexer	lex;

	g_sh.child = FALSE;
	if (valid_line(line))
		return ;
	a_tok = lexer(line, ft_strlen(line), &lex);
	if (a_tok <= 0)
	{
		if (a_tok == FALSE && g_sh.subtok == FALSE)
			perror("error: syntax error\n");
		free_lexer(&lex);
		return ;
	}
	if (parser_astree(&lex))
	{
		free_lexer(&lex);
		return ;
	}
	free(g_sh.astree);
	free_lexer(&lex);
}
