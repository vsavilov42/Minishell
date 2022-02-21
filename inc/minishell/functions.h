/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:11:19 by nortolan          #+#    #+#             */
/*   Updated: 2022/02/21 10:55:50 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//indique el archivo al que corresponde .c y sus funciones

/* export.c */

int	export_env(char **arg);
int	contain_equal(char *arg);
int	contain_equal_cont(char *arg);

/* env */

int	env(char **arg);

/* pwd.c */

int	pwd(char **arg);

/* cd.c */

int	cd(char **arg);

/* echo.c */

int	echo(char **str);
int	verify_echo(char *str);
void	write_echo(char **arg, int index, int n);

/* error.c */

int	error_command(char **cmd);

/* utils.c */

int	error_msg(char *str);
char	*strtolow(char *str);
int	strlen_env(char *env);
void	free_split(char **split);

/* utils_list.c */

t_envlst	*new_envlst(char *env);
t_envlst	*new_envlst_equal(char *env);
t_envlst	*new_envlst_only_name(char *env);
t_envlst	*envlst_last(t_envlst *lst);
void		envlst_add_back(t_envlst **lst, t_envlst *new);

/* init_shell.c */

void	init_minishell(void);
void	get_env(void);

//reading.c
void	get_lines(char *line);

#endif
