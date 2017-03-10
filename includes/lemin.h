/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:33:00 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/06 08:27:57 by abarriel         ###   ########.fr       */
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
	int				by;
	int				x;
	int				y;
	int				start;
	int				end;
	int 			ants;
	struct s_tube	*tube;
	struct s_room	*next;
}					t_room;

typedef struct		s_tube
{
	struct s_tube	*prev;
	struct s_tube	*next;
	struct s_room	*room;
}					t_tube;

typedef struct		s_path
{
	char			*name;
	struct s_room   *r;
	int				size;
	struct s_path	*next;
}					t_path;

typedef struct		s_ant
{
	int				ant;
	int  			bonus_color;
	int  			bonus_path;
}					t_ant;
void				add_back_path(t_path **t, t_room *r, int p);
void				handles_path(t_path **p, t_ant *a, int max_path);
int					check_link(t_room *r, char *s1);
char				*next_comment(char *name);
char				*ft_name_coord(char *name);
void				verif(t_room *r);
t_path				*save_path(t_room *r, int *i);
void				poids(t_room *r);
void				handles_algo(t_room *r, t_ant *a);
void				print_room(t_room *b);
void				check_room(t_room *tmp);
int					check_stopping(t_room *tmp, char *line, int index);
int					if_so_(char conv, char *symb);
int					add_tube(t_room **r, char *line);
t_room				*init_room(char *name, int index);
void				print_path(t_path *path);
void				add_back_room(t_room **r, char *name, int index);
t_ant				*init_ant(char *name, int bp, int bc);
void				parser(int bp, int bc);
#endif
