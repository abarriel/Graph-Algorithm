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

int verif_no_path(t_room *r)
{
	int i;

	i = 0;
	t_tube *tube;
	while(r->tube->prev)
		r->tube = r->tube->prev;
	tube = r->tube;
	while(r->tube)
	{
		// ft_printf("{GRE}[%s by= %d p= %d]\n",r->tube->room->name,r->tube->room->by,r->tube->room->poids);
		if (r->tube->room->by != 4)
			i++;
		r->tube = r->tube->next;
	}
	if (i > 0)
	{
		r->tube = tube;
		return 1;
	}
	else
		return 0;
}

void	save_path_(t_room **rp, t_path **pa, int p)
{
	t_room *r;
	t_tube *tmp;
	t_path *path;

	path = *pa;
	r = *rp;
	// ft_printf("{GRE}%s\n", "DEDANS");
	add_back_path(&path, r->name, r->start, p);
	// ft_printf("{GRE}[%s]\n", r->name);
	while (r && r->end != 1)
	{
		while (r->tube->room->by == 4 || r->tube->room->poids != 1)
				r->tube = r->tube->next;
		// ft_printf("{GRE}[%s]\n", r->name);
		if (r->by != 4 && r->tube->room->poids == 1)
		{
			if(r->start != 1)
			add_back_path(&path, r->name, r->start, p);
			r->by = 4;
			// ft_printf("{PUR}[%s]\n", r->name);
			// while (r->tube->room->by == 4 || r->tube->room->poids != 1)
			// 	r->tube = r->tube->next;
			r = r->tube->room;
		}
		else
		{
			tmp = r->tube;
			// ft_printf("{RED}[%s]\n", tmp->room->name);
			// r->tube = r->tube->next;
			r = r->tube->room;
			// ft_printf("{YEL}[%s]\n", r->tube->room->name);			
		}
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
	// ft_printf("{RED}%s\n", "1");
	if(!r->tube || !verif_no_path(r))
	{
		// ft_printf("{RED}%s\n", "2");
		(*i)++;
		return (path);
	}
	// ft_printf("{RED}{%s}\n", r->name);
	// ft_printf("{RED}%s\n", "5");
	save_path_(&r,&path,p);
	return (path);
}

t_path	*init_path(char *name, int start,  int p)
{
	t_path	*u;

	if (!(u = (t_path*)malloc(sizeof(t_path))))
		ft_exit("Failed to Malloc");
	u->name = name;
	u->ants = 0;
	u->start = start;
	u->size = p;
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
