/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 15:55:02 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/23 16:59:45 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	*ft_name_coord(char *name)
{
	char	*str;

	str = "NULL";
	str = *ft_strsplit(name, ' ');
	return (str);
}

t_room	*init_room(char *name, int index)
{
	t_room	*r;

	if (!(r = (t_room*)malloc(sizeof(t_room))))
		ft_exit("Failed to Malloc");
	r->tube = NULL;
	r->next = NULL;
	r->y = 0;
	r->x = 0;
	r->poids = 0;
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
		ft_exit("Wrong Input of Room");
	if ((*tab[1] < 0 && *tab[1] > 9) || (*tab[2] < 0 && *tab[2] > 9))
		ft_exit("Wrong Coord");
	if ((ft_sdigit(tab[1]) || ft_sdigit(tab[2])))
		ft_exit("Coord not a good number");
}

int		parse_error_room(int index, char *n)
{
	static int	u = 0;

	if_so_('-', n);
	if (*n == '#')
		return (0);
	if (u == 2 && index == 2)
		ft_exit("Plusieur End");
	if (u == 1 && index == 1)
		ft_exit("Plusieur Start");
	parse_error_coord(n);
	u = (index == 2) ? 2 : u;
	u = (index == 1) ? 1 : u;
	return (1);
}

void	add_back_room(t_room **r, char *name, int index)
{
	t_room	*tmp;

	if (!(parse_error_room(index, name)))
		return ;
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
