/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:18 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/12 20:18:47 by dexposit         ###   ########.fr       */
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
//	printf("cuenta de cmd + argumentos: %d\n", cca);
	res = (char **) malloc(sizeof(char *) * (cca + 1));
	if (!res)
		return (NULL);
	res[cca] = NULL;
	while (cmd->argv[++i])
		if (is_cmd(cmd->type_arr, i))
			res[data_save++] = cmd->argv[i];
/*/////PRINT RES TO TEST/////////
	i = -1;
	while (res[++i])
		printf("cmd %d: %s\n", i, res[i]);
////////////////////////////// */
	return (res);
}

int	count_cmd_arg(t_cmd *cmd)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (cmd->argv[i])
		res += is_cmd(cmd->type_arr, i++);
	return (res);
}

int	is_cmd(int	*line, int i)
{
	return ((i == 0 && line[i] == 1)
		|| ((i > 0) && (line[i] == 1) && (line[i - 1] == 1)));
}

char	*access_path_with_cmd(char *path, char *cmd)
{
	char	*aux;
	char	*res;

	aux = ft_strjoin(path, "/");
	free(path);
	res = ft_strjoin(aux, cmd);
	free(aux);
	if (access(res, X_OK))
	{
		free(res);
		res = NULL;
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
