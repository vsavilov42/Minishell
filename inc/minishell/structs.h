/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:12:34 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/17 14:03:24 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//Coloque aquí su estructura

//tokens
typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_reading
{
	int				tok_status;
	int				count;
	int				aux_count;
	int				space_count;
	int				q_count;
	int				q_count_aux;
	int				q_count_aux_2;
	int				q_check;
	char			**env;
	struct s_token	*token;
	struct s_token	*head;
}	t_reading;

#endif
