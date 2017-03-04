/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:52:46 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/01 02:37:15 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	start_algo(t_room *r)
{
	t_tube *tmp;

	while (r->start != 1 && r)
		r = r->next;
	r->poids = 1;
	while (r->end != 1)
	{
		if (r->start == 1 && r->poids == 2)
			exit(0);
		tmp = r->tube;
		while (tmp)
		{
			if (tmp->room->end == 1)
			{
				r = tmp->room;
				r->poids = 1;
				return 0;
			}
			tmp = tmp->next;
		}
		tmp = r->tube;
		if (r->tube == NULL)
			ft_exit("Invalid Path\n");
		if (r->tube->room->poids == 0)
		{
			r->tube->room->poids = 1;
			r = r->tube->room;
		}
		else
		{
			r->tube = r->tube->next;
			if (!r->tube)
			{
				r->poids = 2;
				r->tube = tmp;
				while (r->tube->prev)
					r->tube = r->tube->prev;
				while (r->tube->room->poids != 1 && r->tube->next)
					r->tube = r->tube->next;
				if (r->tube->room->poids != 1 && r->tube->next == NULL)
					ft_exit("Invalid Path");
				r = r->tube->room;
			}
		}
	}
	return 0;
}

void handles_algo(t_room *r, t_ant *a)
{
	start_algo(r);
	print_room_r(r);
	start_algo(r);
	print_room_rj(r);
}