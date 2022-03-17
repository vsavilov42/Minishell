/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:11:19 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/17 11:35:12 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "structs.h"

//indique el archivo al que corresponde .c y sus funciones
//reading.c
void	get_lines(char *line);

//quote_handling.c
int		skip_chars(t_reading *vars, char *line, int i);
void	back_quote_check(t_reading *vars, char *line, int i);
int		aux_count_loop(t_reading *vars, char *line, int i);
int		quote_handling(t_reading *vars, char *line, int i);

//reading_utils.c
void	reading_struct_init(t_reading *vars);
t_token	*last_token(t_token *lst);
void	token_clear(t_reading *vars);

//expansions.c
void	tok_expand(t_reading *vars);

#endif
