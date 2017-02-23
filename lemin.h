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
	int				x;
	int				y;
	int				start;
	int				end;
	struct s_tube	*tube;
	struct s_room	*next;
}					t_room;

typedef struct		s_tube
{
	char			*name;
	int				var;
	struct s_tube	*next;
	struct s_room	*room;
}					t_tube;

typedef struct		s_ant
{
	int				ant;
	struct s_ant	*next;
}					t_ant;
void 				check_room(t_room *tmp);
int 				start_algo(t_room *r, t_ant *a);
int 				check_stopping(t_room *tmp, char *line, int index);
int					if_so_(char conv, char *symb);
int 				add_tube(t_room **r, char *line, int index);
t_room				*init_room(char *name, int index);
void 				add_back_room(t_room **r, char *name, int index);
t_ant				*init_ant(char *name);
t_tube				*init_tube(t_room *r);
int					parser(void);
#endif
