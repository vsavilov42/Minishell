/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:23:23 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/18 18:12:27 by dexposit         ###   ########.fr       */
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
//	int		status;

	aux = cmd->head_cmd;
	if (aux->next || (!aux->next && is_builtin(aux->argv)))
		create_process(aux, NULL);
	else
	{
		printf("builtin\n");
		builtin(aux->argv);
	}
/*
	status = 0;
	while (aux)
	{
		//create_process(g_sh.cmd);
		printf("%s %d\n", *(aux->argv), status++);
		aux = aux->next;
	}
*/
//	waitpid(g_sh.lst_id, &status, 0);
//	exit(status);
}
/*
 * REVISAR COMO DEBEN ESPERARSE LOS PROCESOS
 */
/*
 *	CREATE_PROCESS:
 *
 *	tiene que crear un proceso para cada comando de la estructura t_cmd
 * 	luego de crear los pertinentes procesos se debe ejecutar cada comando en el proceso que corresponda
 * 	antes de eso usaremos dup dependiendo que tipo de cmd sea
 * 		1- para las pipes
 * 		2- luego para las redirecciones < << > >>
 * 		3- cerrar todos los fd no usados
 * 		4- ejecutar el comando
 * 			si no ejecuta: liberar todo y pertinentes status de salia
 */
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
		//execute_cmd(cmd);
	}
		//dup entrada a pipe prev
	//	printf("ultimo hijo: %s\n", *(cmd->argv));
	else if (prev)
		//dup entrada a pipe prev y salida a pipe own
		execute_cmd(cmd);
		//printf("process padre hijo  of the command: %s\n", *(cmd->argv));
	else
		execute_cmd(cmd);
	return (own->pid);
}

t_exec	*initialize_exec_struct(t_cmd *cmd)
{
	t_exec	*res;

	res = (t_exec *) malloc(sizeof(t_exec));
	if (!res)
		return (perror("Fail to reserve memory\n"), free(res), NULL);
	if (cmd->next || (cmd->pos == 0))
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
/*	1  crea el char ** para execve y 2 rellena el cmd->path con la ruta del commando que es.
 */
//	cmd->env = create_path(cmd);
//	command_path(cmd, );

int	execute_cmd(t_cmd *cmd)
{
	char **split_cmd;

	if (!is_builtin(cmd->argv))
		return (builtin(cmd->argv), 0);
	cmd->env = env_pointer();
//	printf("split_cmd\n");
	split_cmd = save_cmd_with_arguments(cmd);
//	printf("cmd???	%s\n", split_cmd[0]);
	cmd->cmd_path = fill_cmd_path(cmd->env, split_cmd[0]);
//	printf("CMD PAHT: %s\n", cmd->cmd_path);
	if (cmd->cmd_path)
		execve(cmd->cmd_path, split_cmd, cmd->env);
//	printf("no se ejecuta\n");
//	printf("----------------------\n");
//	printf("cmd path: %s\n", cmd->cmd_path);	
//	execve(cmd->cmd_path, split_cmd, cmd->env);
	return (-1);
}

/*	
 *	FILL_CMD_PATH:
 *
 *	recortar la línea paht del env
 *	splitear esta línea por : sin la parte del inicio
 *	comprobar con access( ejecución) de cada ruta de nuestro enviroment junto al cmd pasado como argumento.
 	- si el cmd introducido ya es una ruta esta funcion retornará 0
	- en otro caso devolverá el cmd con su ruta en un solo string
 */
char	*fill_cmd_path(char **env, char *cmd)
{
	char	*res;
	int		i;
	char	*aux_path;
	char	**path;
	i = -1;
	res = NULL;
	if (ft_strchr(cmd, '/') != NULL )
		return (res);
	while (env[++i] && ft_strncmp(env[i], "PATH=", 5));
	aux_path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	path = ft_split(aux_path, ':');
	free(aux_path);
/*/////TEST FT_SPLIT////
	i = -1;
	while (path[++i])
		printf("%d-->%s\n", i, path[i]);
*/
	i = -1;
	while (!res && path[++i])
		res = access_path_with_cmd(path[i], cmd);
	return (res);
}

/*
 * UNUSED FUNCTIONS
 */
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

/*	///////TEST CREATE_PATH//////
	int i=-1;
	while (cmd->env[++i])
		printf("linea %d del env:\n%s\n", i, cmd->env[i]);
*/
void	command_path(t_cmd *cmd, char *path_line)
{
	char	**envtmp;
	char	*tmp;
	int	i;

//////DEBUG/////
	if (!path_line)
	{
		printf("NO ARGUMENT PATH_LINE WTF\n");
		return ;
	}
		printf("path line: %s\n", path_line);
///////////////
	envtmp = ft_split(path_line, ':');
	tmp = ft_strjoin("/", *cmd->argv);
	i = -1;
	while (envtmp[++i])
		if (access(ft_strjoin(envtmp[i], tmp), X_OK))
			cmd->cmd_path = ft_strjoin(envtmp[i], tmp);
	if (!cmd->cmd_path)
		ft_putstr_fd("Error: Command not found\n", 2);
}
