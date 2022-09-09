/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:13:38 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/09/07 20:57:18 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		error_msg(char *str);
int		same_strcmp(char *str1, char *str2);
int		strlen_env(char *env);
int		bad_str(char *arg);
void	free_split(char **split);
char	*strtolow(char *str);

char	*ft_cplusic(char *num);

//init_shell
void	init_minishell();
void	flags_handle(int argc, char **argv);

void	get_env();

int	error_ret(const char *s, int code);
int	perror_ret(const char *s, int code);

#endif
