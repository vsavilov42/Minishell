/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:11:36 by nortolan          #+#    #+#             */
/*   Updated: 2022/04/28 12:24:52 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_init(t_parse *parse)
{
	parse->wc = 0;
	parse->wc_aux = 0;
	parse->cmds = NULL;
	parse->head_cmd = NULL;
}

t_cmd	*last_cmd(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	free_args(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

void	cmds_clear(t_parse *parse)
{
	t_cmd	*temp;

	temp = NULL;
	parse->cmds = parse->head_cmd;
	if (parse->cmds == NULL)
		return ;
	while (parse->cmds)
	{
		free_args(parse->cmds->argv);
		temp = parse->cmds;
		free(parse->cmds->type_arr);
		parse->cmds = parse->cmds->next;
		free(temp);
	}
}
