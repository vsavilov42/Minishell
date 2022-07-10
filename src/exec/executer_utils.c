/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:18 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/10 18:35:13 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	new_fork(t_exec *exe)
{
	exe->pid = fork();
	if (exe->pid < 0)
		perror("Fail to execute fork\n");
	return (exe->pid >= 0);
}

char	**save_cmd_with_arguments(t_cmd *cmd)
{
	char	**res;
	int		i;
	int		data_save;
	int		cca;

	data_save = 0;
	i = -1;
	cca = count_cmd_arg(cmd);
	res = (char **) malloc(sizeof(char *) * (cca + 1));
	res[cca] = NULL;
	while (cmd->argv[++i])
	{
		if (cmd->type_arr[i] == 1)
			res[data_save++] = cmd->argv[i];
		else if (cmd->type_arr[i] == 8)
			res[data_save++] = cmd->argv[i]; 
	}
	i = -1;
	while (res[++i])
		printf("cmd %d: %s\n", i, res[i]);
	return (res);
}

int	count_cmd_arg(t_cmd *cmd)
{
	int	i;
	int	res;

	res = 0;
	i = -1;
	while (cmd->argv[++i])
	{
		if (cmd->type_arr[i] == 1 || cmd->type_arr[i] == 8)
			res++;
	}
	return (res);
}

/*
void	modify_in_out_cmd(t_cmd *cmd, t_exec *prev, t_exec *own)
{
	//esta función va a usar dup2 en las redirecciones menos pipes
	//1 para los infiles
	//2 para los outfiles
}
*/
