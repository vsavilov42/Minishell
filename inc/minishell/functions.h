/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:11:19 by nortolan          #+#    #+#             */
/*   Updated: 2022/07/22 20:11:21 by Vsavilov         ###   ########.fr       */
/*   Updated: 2022/03/17 14:55:04 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "structs.h"

/* command_analyze.c */

int		is_builtin(char **cmd);
void	command_analyze(t_cmd *cmds);
void	command_exec(t_cmd *cmds);
void	standard_command(char **arg);
void	exec_one_command(t_cmd *cmds);
char	**env_pointer(void);
char	**create_path(t_cmd *cmd);

/* quote_handlin.c */

int		skip_chars(t_reading *vars, char *line, int i);
int		aux_count_loop(t_reading *vars, char *line, int i);
int		quote_handling(t_reading *vars, char *line, int i);
void	back_quote_check(t_reading *vars, char *line, int i);

/* expansions.c */

void	tok_expand(t_reading *vars);

/* reading_utils.c */

void	reading_struct_init(t_reading *vars);
t_token	*last_token(t_token *lst);
void	token_clean(t_reading *vars);

/* error.c */

int		error_command(char **cmd);

/* init_shell.c */

void	init_minishell(void);
void	get_env(void);

//reading.c
void	get_lines(char *line);

//quote_handling.c
int		skip_chars(t_reading *vars, char *line, int i);
int		aux_count_loop(t_reading *vars, char *line, int i);
int		quote_handling(t_reading *vars, char *line, int i);
void	back_quote_check(t_reading *vars, char *line, int i);

//reading_utils.c
void	reading_struct_init(t_reading *vars);
t_token	*last_token(t_token *lst);
void	token_clear(t_reading *vars);
int		tok_status_check(t_reading *vars, char *line, int i);
int		check_pipes(t_reading *vars);

//expansions.c
void	tok_expand(t_reading *vars);

//remove_quotes.c
void	remove_quotes(t_reading *vars);

//parse.c
void	parse(t_reading *vars);

//parse_utils.c
void	parse_init(t_parse *parse);
t_cmd	*last_cmd(t_cmd *lst);
void	cmds_clear(t_parse *parse);

#endif
