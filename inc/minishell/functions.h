/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:11:19 by nortolan          #+#    #+#             */
/*   Updated: 2022/02/17 11:50:55 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//indique el archivo al que corresponde .c y sus funciones

/* cd.c */

int	cd(char **arg);

/* echo.c */

int	echo(char **str);
int	verify_echo(char *str);
void	write_echo(char **arg, int index, int n);

/* utils.c */

int	error_msg(char *str);
char	*strtolow(char *str);

//reading.c
void	get_lines(char *line);

#endif
