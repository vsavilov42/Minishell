/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:21:08 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/22 19:21:28 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVLST_H
# define ENVLST_H

t_envlst	*new_envlst(char *env);
t_envlst	*new_envlst_only_name(char *env);
t_envlst	*new_envlst_equal(char *env);
t_envlst	*envlst_last(t_envlst *lst);
void		envlst_add_back(t_envlst **lst, t_envlst *new);

void		envlst_clear(t_envlst **lst, void (*del)(void *));

#endif
