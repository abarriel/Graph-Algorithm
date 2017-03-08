/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 02:15:55 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/06 07:30:15 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	save_path_(t_room **rp, t_path **pa, int p)
{
	t_room *r;
	t_path *path;

	path = *pa;
	r = *rp;
	while (r && r->end != 1)
	{
		add_back_path(&path, r->name, r->start, p);
		if (r->by != 4 && r->tube->room->poids == 1)
		{
			r->by = 4;
			while (r->tube->room->by == 4 || r->tube->room->poids != 1)
				r->tube = r->tube->next;
			r = r->tube->room;
		}
		else if (r->by == 4)
			r->tube = r->tube->next;
		p++;
	}
	add_back_path(&path, r->name, r->start, p);
	*pa = path;
	*rp = r;
}

t_path	*save_path(t_room *r, int *i)
{
	t_path	*path;
	int		p;

	p = 1;
	path = NULL;
	while (r && r->start != 1)
		r = r->next;
	if (!r->tube)
		return (NULL);
	if (r->poids == 2)
	{
		(*i)++;
		return (path);
	}
	r->by = 0;
	save_path_(&r,&path,p);
	return (path);
}

t_path	*init_path(char *name, int start,  int p)
{
	t_path	*u;

	if (!(u = (t_path*)malloc(sizeof(t_path))))
		ft_exit("Failed to Malloc");
	u->name = name;
	u->start = start;
	u->size += p;
	u->next = NULL;
	return (u);
}

void	add_back_path(t_path **t, char *name, int start, int p)
{
	t_path	*tmp;

	tmp = *t;
	if (!tmp)
	{
		*t = init_path(name, start, p);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_path(name, start, p);
	tmp = tmp->next;
}
