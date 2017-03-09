/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 05:02:47 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/06 07:36:57 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_path(t_path *path)
{
	if (!path)
		return ;
	while (path)
	{
		// ft_printf("[%s-%d]", path->name, path->size);
		ft_printf("%s", path->name);
		if (path->next)
			ft_printf("->");
		path = path->next;
	}
	ft_printf("\n\n");
}

void	print_room_r(t_room *r)
{
	while (r && r->start != 1)
		r = r->next;
	r->by = 0;
	r->tube->room->poids = 1;
	while (r && r->end != 1)
	{
		ft_printf("{GRE}%s %d %d\n", r->name, r->poids, r->by);
		if (r->by != 5 && r->by != 4 && r->by != 6 && r->tube->room->poids == 1)
		{
			r->by = 4;
			while (r->tube->room->by == 4 || r->tube->room->poids != 1)
				r->tube = r->tube->next;
			r = r->tube->room;
		}
		else if (r->by == 4)
			r->tube = r->tube->next;
	}
	ft_printf("{GRE}%s %d End= %d\n\n", r->name, r->poids, r->end);
}

void	print_room(t_room *r1)
{
	t_room *r;

	r = r1;
	while (r)
	{
		if (r->start == 1)
			ft_printf("{RED}%s%s", "S=", r->name);
		else if (r->end == 1)
			ft_printf("{RED}%s%s", "E=", r->name);
		else
			ft_printf("{GRE}%s", r->name);
		if (r->tube == NULL)
			r = r->next;
		else
		{
			while (r->tube)
			{
				ft_printf("{YEL} - %s", r->tube->room->name);
				r->tube = r->tube->next;
			}
			r = r->next;
		}
		ft_printf("\n");
	}
}
