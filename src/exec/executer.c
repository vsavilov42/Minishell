/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:23:23 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/22 13:44:15 by dexposit         ###   ########.fr       */
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
	pid_t	id;

	aux = cmd->head_cmd;
	if (!aux->next && !is_builtin(aux->argv))
		return(execute_cmd(aux), (void) 0);
		//ejecutar un builtin normal
	else
	{
		id = fork();
		if (id < 0)
			perror("Fail doing fork.\n");
		else if (id == 0)	
			create_process(aux, NULL);
		else
			waitpid(-1, &status, 0);
/*	i = 0;
	while (g_sh.pid[i++]);
	while(g_sh.pid[--i])
			waitpid(g_sh.pid[i], &status, 0);
			// Aquí tenemos usar waitpid para todos los id de cada proceso
//			while (wait(&status) > 0);*/
	}
	waitpid(-1, &status, 0);
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
	t_exec *own;

	//este es el caso en el que ultimo commando
	own = initialize_exec_struct(cmd);
	if (!cmd->next)
		if (!prev)
			pipes_selector(0, own, prev, cmd);
//			dup_in_out();
//			printf("este es un único commando.\n");
		else
			pipes_selector(1, own, prev, cmd);
//			printf("aqui hacemos dup de entrada a prev->pipe\n");
//			dup_in_out();
	else
	//este son los casos en los que hay mas de un commando
	{
		//	caso 1:	cmd | cmd --> primer comando con mas detrás
		//	caso 2: cmd | cmd | cmd -->commando con uno delante y uno detrás
		own->pid = fork();
//		save_pid(own->pid);
		if (own->pid < 0)
			perror("Fail to fork.\n");
		else if (own->pid == 0)
			create_process(cmd->next, own);
		else if (!prev)
			pipes_selector(2, own, prev, cmd);
//			printf("aque hacemos dup de salida a own->pipe.\n");
		else if (prev)
			pipes_selector(3, own, prev, cmd);
//		printf("aqui haceos dup stdin a prev->pipe y salida a own->pipe\n");
	}
	//close unused fd
//	printf("FUERA IF-ELSE\n");
	//if (own->pid >= 0)
//	execute_cmd(cmd);
	//printf("test: %s\n", cmd->argv[1]);
	//free all, prepare exits
//	waitpid(-1, &own->status, 0);
	return (own->pid);
}

t_exec	*initialize_exec_struct(t_cmd *cmd)
{
	t_exec	*res;

	res = (t_exec *) malloc(sizeof(t_exec));
	if (!res)
		return (perror("Fail to reserve memory\n"), free(res), NULL);
	if (cmd->next)
		pipe(res->pipe_fd);
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
	split_cmd = save_cmd_with_arguments(cmd);
	cmd->cmd_path = fill_cmd_path(cmd->env, split_cmd[0]);
	if (cmd->cmd_path)
		execve(cmd->cmd_path, split_cmd, cmd->env);
	else
	{
		//separate_path_of_cmd(split_cmd, &cmd->cmd_path);
		//execve(NULL, split_cmd, cmd->env);
	}
	//exit(126);
	return (1);

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
