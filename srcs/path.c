/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 02:15:55 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/11 08:02:30 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		verif_no_path(t_room *r)
{
	int		i;
	t_tube	*tube;

	i = 0;
	while (r->tube->prev)
		r->tube = r->tube->prev;
	tube = r->tube;
	while (r->tube)
	{
		if (r->tube->room->by != 4)
			i++;
		r->tube = r->tube->next;
	}
	if (i > 0)
	{
		r->tube = tube;
		return (1);
	}
	else
		return (0);
}

void	save_path_(t_room **rp, t_path **pa, int p)
{
	t_room	*r;
	t_path	*path;

	path = *pa;
	r = *rp;
	add_back_path(&path, r, p);
	while (r && r->end != 1)
	{
		while (r->tube && (r->tube->room->by == 4 || r->tube->room->poids != 1))
			r->tube = r->tube->next;
		if (r->by != 4 && r->tube->room->poids == 1)
		{
			if (r->start != 1)
				add_back_path(&path, r, p);
			r->by = 4;
			r = r->tube->room;
		}
		else
			r = r->tube->room;
		p++;
	}
	add_back_path(&path, r, p);
	*pa = path;
	*rp = r;
}

t_path	*save_path(t_room *r, int *i)
{
	t_path	*path;
	int		p;

	p = 1;
	path = NULL;
	if (!r->tube || !verif_no_path(r))
	{
		(*i)++;
		return (path);
	}
	save_path_(&r, &path, p);
	return (path);
}

t_path	*init_path(t_room *r, int p)
{
	t_path	*u;

	if (!(u = (t_path*)malloc(sizeof(t_path))))
		ft_exit("Failed to Malloc");
	u->r = r;
	u->name = r->name;
	u->size = p;
	u->next = NULL;
	return (u);
}

void	add_back_path(t_path **t, t_room *r, int p)
{
	t_path	*tmp;

	tmp = *t;
	if (!tmp)
	{
		*t = init_path(r, p);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_path(r, p);
	tmp = tmp->next;
}
