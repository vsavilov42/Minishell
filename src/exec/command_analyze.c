/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analyze.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:26:51 by nortolan          #+#    #+#             */
/*   Updated: 2022/05/20 14:26:00 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syntax_check(t_cmd *cmds)
{
	int	i;
	int	check;

	check = 1;
	while (cmds && check)
	{
		i = -1;
		while (cmds->argv[++i] && check)
		{
			//printf("argv: %s, type: %d\n", cmds->argv[i], cmds->type_arr[i]);
			if (cmds->type_arr[i] != 1)
			{
				if (cmds->argv[i + 1] == NULL)
				{
					write (2, "syntax error near unexpected token `newline'\n", 45);
					check = 0;
				}
				else if (cmds->type_arr[i + 1] != 1)
				{
					write (2, "syntax error near unexpected token `", 36);
					write (2, cmds->argv[i + 1], ft_strlen(cmds->argv[i + 1]));
					write (2, "'\n", 2);
					check = 0;
				}
			}
		}
		cmds = cmds->next;
	}
}

void	command_analyze(t_cmd *cmds)
{
	syntax_check(cmds);
	builtin(cmds->argv);
}
