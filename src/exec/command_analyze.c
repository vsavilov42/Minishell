/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analyze.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:26:51 by nortolan          #+#    #+#             */
/*   Updated: 2022/06/01 16:16:12 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: "<<" solo falla;
//TODO: por cada heredoc, abres un archivo (temp1, temp2, etc por ejemplo),
//		escribes en el lo que haya en el heredoc y lo cierras, el exec tendrá
//		que acceder a ellos mas adelante. cada uno tiene su file descriptor

int	syntax_aux(t_cmd *cmds, int i, int mode)
{
	if (mode == 1)
		write (2, "syntax error near unexpected token `newline'\n", 45);
	if (mode == 0)
	{
		write (2, "syntax error near unexpected token `", 36);
		write (2, cmds->argv[i + 1], ft_strlen(cmds->argv[i + 1]));
		write (2, "'\n", 2);
	}
	return (0);
}

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
			if (cmds->type_arr[i] != 1)
			{
				if (cmds->argv[i + 1] == NULL)
					check = syntax_aux(cmds, i, 1);
				else if (cmds->type_arr[i + 1] != 1)
					check = syntax_aux(cmds, i, 0);
			}
		}
		cmds = cmds->next;
	}
}

int	heredoc_reading(t_here *here, int i)
{
	int		loop_fd;

	here->line = readline("> ");
	if (here->line == NULL)
		return (-1);
	//printf("testDELS: %s\n", dels[count]);
	//printf("testLINE: %s\n", line);
	if (ft_strncmp(here->line, here->dels[here->count],
			ft_strlen(here->dels[here->count])) == 0
		&& ft_strlen(here->line) == ft_strlen(here->dels[here->count]))
	{
		i++;
		here->count++;
	}
	else
	{
		loop_fd = open(here->file, O_RDWR | O_APPEND, 0644);
		write (loop_fd, here->line, ft_strlen(here->line));
		write (loop_fd, "\n", 1);
		close(loop_fd);
	}
	free(here->line);
	return (i);
}

void	here_loop(t_cmd *cmds, t_here *here)
{
	int		i;
	int		fd;
	char	*num;

	here->count = 0;
	i = -1;
	while (cmds->argv[++i])
	{
		printf("test2: %s\n", cmds->argv[i]);
		if (cmds->type_arr[i] == 6)
		{
			num = ft_itoa(here->file_num);
			here->file = ft_strjoin("/tmp/temp", num);
			printf("file: %s\n", here->file);
			here->free_check = 1;
			here->file_num++;
			fd = open(here->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		while (cmds->type_arr[i] == 6)
		{
			i = heredoc_reading(here, i);
			if (i < 0)
				break ;
		}
		if (here->free_check)
		{
			free(num);
			free(here->file);
			here->free_check = 0;
			close(fd);
		}
	}
}

void	here_doc(t_cmd *cmds, t_here *here)
{
	int		i;
//	int		count;
//	char	**dels;

//	count = 0;
	while (cmds)
	{
		i = -1;
		while (cmds->argv[++i])
		{
			if (cmds->type_arr[i] == 6)
				here->count++;
		}
		here->dels = malloc(sizeof(char *) * (here->count + 1));
		if (here->dels == NULL)
			exit (1);
		i = -1;
		here->count = 0;
		while (cmds->argv[++i])
		{
			if (cmds->type_arr[i] == 6)
				here->dels[here->count++] = ft_strdup(cmds->argv[i + 1]);
		}
		here->dels[here->count] = NULL;
		//////////TESTTTTTT/////////////
		here->count = -1;
		while (here->dels[++here->count])
			printf("dels: %s\n", here->dels[here->count]);
		printf("dels: %s\n", here->dels[here->count]);
		printf("-------------------------\n");
		////////////////////////////////
		here_loop(cmds, here);
		free_args(here->dels);
		cmds = cmds->next;
	}
}

void	here_init(t_here *here)
{
	here->file_num = 0;
	here->free_check = 0;
	here->count = 0;
}

void	command_analyze(t_cmd *cmds, t_cmd *head_cmd)
{
	t_here	here;

	syntax_check(cmds);
	cmds = head_cmd;
	here_init(&here);
	here_doc(cmds, &here);
	builtin(cmds->argv);
}
