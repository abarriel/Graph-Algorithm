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

void	change_r(t_room *r)
{
	while (r)
	{
		r->by = 0;
		while (r->tube->next)
		{
			if (r->tube->room->poids != 0)
				r->tube->room->poids = 0;
			r->tube = r->tube->next;
		}
		while (r->tube->prev)
			r->tube = r->tube->prev;
		if (r->start == 1)
		{
			r->start = 0;
			r->end = 1;
			r->x = 45;
		}
		if (r->end == 1 && r->x != 45)
		{
			r->end = 0;
			r->start = 1;
		}
		r = r->next;
	}
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
	while (r && r->end != 1)
	{
		add_back_path(&path, r->name, p);
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
	add_back_path(&path, r->name, p);
	return (path);
}

t_path	*init_path(char *name, int p)
{
	t_path	*u;

	if (!(u = (t_path*)malloc(sizeof(t_path))))
		ft_exit("Failed to Malloc");
	u->name = name;
	u->size += p;
	u->next = NULL;
	return (u);
}

void	add_back_path(t_path **t, char *name, int p)
{
	t_path	*tmp;

	tmp = *t;
	if (!tmp)
	{
		*t = init_path(name, p);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_path(name, p);
	tmp = tmp->next;
}
