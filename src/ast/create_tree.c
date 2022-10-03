/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:55:39 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/03 20:56:48 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_ast(t_ast *ast, int j)
{
	int		node;
	char	*type;

	if (!ast)
		return ;
	int i = -1;
	while (++i < j + 10)
		printf(" ");
	node = astree_get_type(ast);
	if (node & NODE_PIPE)
		type = ft_strdup("|");
	else if (node & NODE_SEQ)
		type = ft_strdup(";");
	else if (node & NODE_REDIR)
		type = ft_strdup("redir");
	else if (node & NODE_RD_IN)
		type = ft_strdup("<");
	else if (node & NODE_HEREDOC)
		type = ft_strdup("<<");
	else if (node & NODE_TRUNC)
		type = ft_strdup(">");
	else if (node & NODE_APPEND)
		type = ft_strdup(">>");
	else if (node & NODE_AND)
		type = ft_strdup("&&");
	else if (node & NODE_OR)
		type = ft_strdup("||");
	else if (node & NODE_CMD)
		type = ft_strdup("command");
	else if (node & NODE_ARG)
		type = ft_strdup("argument");
	else
		type = ft_strdup("wtf is that");

	if (ast->type & NODE_DATA)
		printf("Type: [%s], Data: [%s]\n", type, ast->data);
	else
		printf("Type: [%s]\n", type);
	free(type);
	print_ast(ast->left, j + 10);
}

void	create_tree(t_ast **ast, t_lexer *lex)
{
	g_sh.astree = (t_ast **)malloc(sizeof(t_ast *));
	if (!g_sh.astree)
		ft_putstr_fd("malloc", 1);
	*g_sh.astree = NULL;
	g_sh.tok = lex->tok_lst;
	*ast = cmd_line(); // create every case
	print_ast(*ast, 0);
}
