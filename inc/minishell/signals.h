/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:11:31 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/05 13:18:00 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define SIG_ERROR 130

void	manage_signal(void);
void	signal_heredoc(void);
void	signal_child(void);
void	signal_ignore(void);
int	status_exit(int status);

void	free_all(void);

#endif
