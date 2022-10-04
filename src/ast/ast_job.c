/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:50:08 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/04 13:30:30 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_ast	*job4(void)
{
	return (simple_cmd());
}

static t_ast	*job3(void)
{
	t_ast	*cmd_node;

	if (!ast_valid_char(NULL, TOK_LPRTH))
		return (NULL);
	cmd_node = simple_cmd();
	if (!cmd_node)
		return (NULL);
	if (!ast_valid_char(NULL, TOK_RPRTH))
	{
		astree_del_node(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}

static t_ast	*job2(void)
{
	t_ast	*job_node;
	t_ast	*cmd_node;
	t_ast	*result;

	cmd_node = simple_cmd();
	if (!cmd_node)
		return (NULL);
	if (!ast_valid_char(NULL, TOK_PIPE))
	{
		astree_del_node(cmd_node);
		return (NULL);
	}
	job_node = job();
	if (!job_node)
	{
		astree_del_node(cmd_node);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_PIPE);
	astree_root_branch(result, cmd_node, job_node);
	return (result);
}

static t_ast	*job1(void)
{
	t_ast	*job_node;
	t_ast	*cmd_node;
	t_ast	*result;

	if (!ast_valid_char(NULL, TOK_LPRTH))
		return (NULL);
	cmd_node = simple_cmd();
	if (!cmd_node)
		return (NULL);
	if (!ast_valid_char(NULL, TOK_RPRTH)
		|| !ast_valid_char(NULL, TOK_PIPE))
	{
		astree_del_node(cmd_node);
		return (NULL);
	}
	job_node = job();
	if (!job_node)
	{
		astree_del_node(job_node);
		return (NULL);
	}
	result = (t_ast *)malloc(sizeof(t_ast));
	astree_set_type(result, NODE_PIPE);
	astree_root_branch(result, cmd_node, job_node);
	return (result);
}

t_ast	*job(void)
{
	t_ast	*new_node;
	t_token	*save;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = job1();
	if (new_node)
	{
		printf("job1 ");
		return (new_node);
	}
	g_sh.tok = save;
	new_node = job2();
	if (new_node)
	{
		printf("job2 ");
		return (new_node);
	}
	g_sh.tok = save;
	new_node = job3();
	if (new_node)
	{
		printf("job3 ");
		return (new_node);
	}
	g_sh.tok = save;
	new_node = job4();
	if (new_node)
	{
		printf("job4 ");
		return (new_node);
	}
	return (NULL);
}
