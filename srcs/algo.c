/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:52:46 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/06 07:17:00 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	verif(t_room *r)
{
	while (r)
	{
		if (r->poids == 1)
			r->poids = 0;
		r = r->next;
	}
}

void	algo_lem__(t_room **r1, t_tube **tmp1, t_room *begin)
{
	t_room	*r;
	t_tube	*tmp;

	r = *r1;
	tmp = *tmp1;
	r->tube = r->tube->next;
	if (!r->tube)
	{
		r->poids = 2;
		verif(begin);
		r = begin;
	}
	*r1 = r;
	*tmp1 = tmp;
}

int		algo_lem_(t_room **r1, t_tube **tmp1, t_room *begin)
{
	t_room	*r;
	t_tube	*tmp;

	r = *r1;
	tmp = *tmp1;
	if (r->tube == NULL)
		return (0);
	if (r->tube->room->poids == 0)
	{
		r->tube->room->poids = 1;
		r = r->tube->room;
	}
	else
		algo_lem__(&r, &tmp, begin);
	*r1 = r;
	*tmp1 = tmp;
	return (1);
}

void	algo_lem(t_room *r)
{
	t_tube	*tmp;
	t_room	*begin;

	begin = r;
	while (r->start != 1 && r)
		r = r->next;
	r->poids = 1;
	while (r->end != 1)
	{
		tmp = r->tube;
		while (tmp)
		{
			if (tmp->room->end == 1)
			{
				r = tmp->room;
				r->poids = 1;
				return ;
			}
			tmp = tmp->next;
		}
		tmp = r->tube;
		if (!algo_lem_(&r, &tmp, begin))
			return ;
	}
	return ;
}

int		multi_path(t_room *r, t_ant *a)
{
	int		tube;
	t_tube	*tmp;

	tube = 0;
	while (r && r->start != 1)
		r = r->next;
	tmp = r->tube;
	while (tmp)
	{
		tmp = tmp->next;
		tube++;
	}
	if (a->ant < tube)
		tube = a->ant;
	return (tube);
}

void	handles_algo(t_room *r, t_ant *a)
{
	t_path	**path;
	int		i;
	int		b;
	int		j;

	i = 0;
	b = 0;
	j = multi_path(r, a);
	path = (t_path **)malloc(sizeof(t_path *) * j);
	while (i == 0 && b < j)
	{
		algo_lem(r);
		path[b] = save_path(r, &i);
		if (!path[0])
			ft_exit("Invalid Path");
		print_path(path[b]);
		b++;
	}
	// handles_path(path, a);
}
