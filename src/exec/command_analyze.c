/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analyze.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:26:51 by nortolan          #+#    #+#             */
/*   Updated: 2022/05/30 14:23:16 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: "<<" solo falla;
//TODO: por cada heredoc, abres un archivo (temp1, temp2, etc por ejemplo),
//		escribes en el lo que haya en el heredoc y lo cierras, el exec tendrá
//		que acceder a ellos mas adelante. cada uno tiene su file descriptor

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

void	here_loop(int count, char **dels, t_cmd *cmds)
{
	int		i;
//	int		fd;
//	int		loop_fd;
	char	*line;

	count = 0;
	i = -1;
	while (cmds->argv[++i])
	{
		printf("test2: %s\n", cmds->argv[i]);
		while (cmds->type_arr[i] == 6)
		{
			line = readline("> ");
			if (line == NULL)
				break ;
			//printf("testDELS: %s\n", dels[count]);
			//printf("testLINE: %s\n", line);
			if (ft_strncmp(line, dels[count], ft_strlen(dels[count])) == 0
				&& ft_strlen(line) == ft_strlen(dels[count]))
				{
					i++;
					count++;
				}
			free(line);
		}
	}
}

void	here_doc(t_cmd *cmds)
 {
	int		i;
	int		count;
//	int		fd;
//	int		loop_fd;
	char	**dels;

	count = 0;
	while (cmds)
	{
		i = -1;
		while (cmds->argv[++i])
		{
			if (cmds->type_arr[i] == 6)
				count++;
		}
		dels = malloc(sizeof(char *) * (count + 1));
		if (dels == NULL)
			exit (1);
		i = -1;
		count = 0;
		while (cmds->argv[++i])
		{
			if (cmds->type_arr[i] == 6)
				dels[count++] = ft_strdup(cmds->argv[i + 1]);
		}
		dels[count] = NULL;
		//////////TESTTTTTT/////////////
		count = -1;
		while (dels[++count])
			printf("dels: %s\n", dels[count]);
		printf("dels: %s\n", dels[count]);
		printf("-------------------------\n");
		////////////////////////////////
		here_loop(count, dels, cmds);
		free_args(dels);
		cmds = cmds->next;
	}
}

void	command_analyze(t_cmd *cmds, t_cmd *head_cmd)
{
	syntax_check(cmds);
	cmds = head_cmd;
	here_doc(cmds);
	builtin(cmds->argv);
}
