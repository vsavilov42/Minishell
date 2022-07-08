/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:23:23 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/08 17:56:10 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	To execute the cmds:
 *	1-	create process
 *		- use fork
 *		- use dup2 in infile and outfile
 *		- if there is a pipe repeat with next command
 *		- execute cmd
 *	2-	check and change the infile and outfile
 *	3-	execute
 *			builtin
 *			execve
*/

void	executer(t_parse *cmd)
{
	t_cmd	*aux;
	int		status;

	aux = cmd->head_cmd;
	create_process(aux, NULL);
/*	while (aux)
	{
		//create_process(g_sh.cmd);
		printf("%s\n", *(aux->argv));
		aux = aux->next;
	}*/
	waitpid(g_sh.lst_id, &status, 0);
//	exit(status);
}

pid_t	create_process(t_cmd *cmd, t_exec *prev)
{
	t_exec	*own;

	own = initialize_exec_struct(cmd);
	if (!own)
		return (-1);
	else if (own->pid == 0 && cmd->next)
		create_process(cmd->next, own);
	else if (own->pid == 0 && !cmd->next)
	{
		g_sh.lst_id = own->pid;
		execute_cmd(cmd);
	}
		//dup entrada a pipe prev
	//	printf("ultimo hijo: %s\n", *(cmd->argv));
	else if (prev)
		//dup entrada a pipe prev y salida a pipe own
		execute_cmd(cmd);
		//printf("process padre hijo  of the command: %s\n", *(cmd->argv));
	else
		//dup salida a pipe own
		execute_cmd(cmd);
		//printf("1processo cmd %s\n", *(cmd->argv));
		//
//	if (prev)
//		waitpid(prev->pid, &prev->status, 0);
	//modify_in_out_cmd(cmd, prev, own);
	// modificar stdin stdout of the command: by pipes < > >> <<
		//identificar que tipo es
		//comprobar los diferentes permisos dependiendoo del caso
		//en caso de heredoc crearlo con un archivo temporal
	//	PREGUNTAR SI ESTE ES EL ORDEN CORRECTO DE BASH O NO
		// 1 pipes 2 infile 3 outfile
	// recortar comando con argumentos: ls -la
		//comprobar si es ruta absoluta o relativa
		//prepar arg para execve y ejecutar
	return (own->pid);
}

t_exec	*initialize_exec_struct(t_cmd *cmd)
{
	t_exec	*res;

	res = (t_exec *) malloc(sizeof(t_exec *));
	if (!res)
		return (perror("Fail to reserve memory\n"), NULL);
	if (cmd->next)
	{
		pipe(res->pipe_fd);
		if (!new_fork(res))
		{
			free(res);
			res = NULL;
		}
	}
	return (res);
}

void	execute_cmd(t_cmd *cmd)
{
//	char **split_cmd;

	if (!is_builtin(cmd->argv))
		return (builtin(cmd->argv));
	//printf("split_cmd\n");
//	split_cmd = save_cmd_with_arguments(cmd);
	//printf("----------------------\n");
//	cmd->env = create_path(cmd);
//	command_path(cmd, );
	//printf("cmd path: %s\n", cmd->cmd_path);	
//	execve(cmd->cmd_path, split_cmd, cmd->env);
	//guardar commando con argumentos doble puntero nulo al final
}
char	**create_path(t_cmd *cmd)
{
	char	**env;
	char	*path_line;
	int	i;

	env = env_pointer();
	i = -1;
	if (**cmd->argv == '/' || **cmd->argv == '.' || access(*cmd->argv, X_OK) == 0)
		cmd->cmd_path = *cmd->argv;
	else
	{
		while (env[++i])
		{
			if (!same_strcmp("PATH=", env[i]))
				path_line = ft_substr(env[i], 5, ft_strlen(env[i]));
			if (!path_line)
				{
					ft_putstr_fd("Error: Path not found\n", 2);
					return (NULL);
				}
		}
		command_path(cmd, path_line);
	}
	return (env);
}

void	command_path(t_cmd *cmd, char *path_line)
{
	char	**envtmp;
	char	*tmp;
	int	i;

	envtmp = ft_split(path_line, ':');
	tmp = ft_strjoin("/", *cmd->argv);
	i = -1;
	while (envtmp[++i])
		if (access(ft_strjoin(envtmp[i], tmp), X_OK))
			cmd->cmd_path = ft_strjoin(envtmp[i], tmp);
	if (!cmd->cmd_path)
		ft_putstr_fd("Error: Command not found\n", 2);
}
