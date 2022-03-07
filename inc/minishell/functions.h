/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:11:19 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/01 10:44:18 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//indique el archivo al que corresponde .c y sus funciones

/* unset.c */

int	unset(char **arg);

/* utils_unset.c */

void	remove_lst(char *name);

/* export.c */

int	export_env(char **arg);
int	contain_equal(char *arg);
int	contain_equal_cont(char *arg);

/* utils_export.c */

void	add_environ(char *arg);
void	replace_environ(char *arg);
void	print_lst(void);
int	compare_lst(char *arg);

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
int	same_strcmp(char *str1, char *str2);
char	*strtolow(char *str);
int	strlen_env(char *env);
void	free_split(char **split);
int	bad_str(char *arg);


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
