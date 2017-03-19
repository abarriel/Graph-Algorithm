/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 15:55:02 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/19 05:38:40 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*init_room(char *name, int index)
{
	t_room	*r;

	if (!(r = (t_room*)malloc(sizeof(t_room))))
		ft_exit("Failed to Malloc");
	r->tube = NULL;
	r->next = NULL;
	r->y = 0;
	r->x = 0;
	r->by = 0;
	r->poids = 0;
	r->ants = 0;
	r->name = ft_name_coord(name);
	r->start = (index == 1) ? 1 : 0;
	r->end = (index == 2) ? 1 : 0;
	return (r);
}

void	parse_error_coord(char *s)
{
	char	**tab;
	int		i;

	i = -1;
	tab = ft_strsplit(s, ' ');
	while (tab[++i])
		;
	if (i != 3)
		ft_exit("Wrong input of room");
	if ((*tab[1] < 0 && *tab[1] > 9) || (*tab[2] < 0 && *tab[2] > 9))
		ft_exit("Wrong coord");
	if ((ft_sdigit(tab[1]) || ft_sdigit(tab[2])))
		ft_exit("Coord not a good number");
	free_split(tab);
}

int		parse_error_room(int index, char *n)
{
	static int	u = 0;
	int			i;

	i = 0;
	if_so_('-', n);
	if (*n == '#')
	{
		ft_strdel(&n);
		return (0);
	}
	while (n[i] && n[i] != ' ')
	{
		if (n[i] == '-')
			ft_exit("Room cant containt -  # L further explication");
		i++;
	}
	if (ft_strchr(n + 1, '#') || *n == 'L')
		ft_exit("Room cant containt -  # L further explication");
	(u == 2 && index == 2) ? ft_exit("More than one end") : NULL;
	(u == 1 && index == 1) ? ft_exit("More than one end") : NULL;
	parse_error_coord(n);
	u = (index == 2) ? 2 : u;
	u = (index == 1) ? 1 : u;
	return (1);
}

void	check_if(t_room *r, char *name)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (name[i] && name[i] != ' ')
		i++;
	tmp = ft_strsub(name, 0, i);
	while (r)
	{
		if (!ft_strcmp(r->name, tmp))
			ft_exit("Same Room");
		r = r->next;
	}
	ft_strdel(&tmp);
}

void	add_back_room(t_room **r, char *name, int index)
{
	t_room	*tmp;

	if (index == 1 || index == 2)
		name = next_comment(name, &index);
	if (!(parse_error_room(index, name)))
		return ;
	check_if(*r, name);
	tmp = *r;
	if (!tmp)
	{
		*r = init_room(name, index);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_room(name, index);
}
