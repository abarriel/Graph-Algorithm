/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:33:00 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/19 11:33:01 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"
# include "limits.h"

typedef struct		s_room
{
	char			*name;
	int				poids;
	int 			dj;
	int				by;
	int				x;
	int				y;
	int				start;
	int				end;
	struct s_tube	*tube;
	struct s_room	*next;
}					t_room;

typedef struct		s_tube
{
	struct s_tube 	*prev;
	struct s_tube	*next;
	struct s_room	*room;
}					t_tube;

typedef struct		s_ant
{
	int				ant;
	struct s_ant	*next;
}					t_ant;
void				poids(t_room *r);
void 				handles_algo(t_room *r, t_ant *a);
void				print_room(t_room *b);
void 				check_room(t_room *tmp);
int 				check_stopping(t_room *tmp, char *line, int index);
int					if_so_(char conv, char *symb);
int 				add_tube(t_room **r, char *line, int index);
t_room				*init_room(char *name, int index);
void				print_room_r(t_room *r1);
void				print_room_rj(t_room *r);
void				print_room_rj4(t_room *r);
void 				add_back_room(t_room **r, char *name, int index);
t_ant				*init_ant(char *name);
int					parser(void);
#endif
