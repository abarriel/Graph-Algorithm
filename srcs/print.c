/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 05:02:47 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/04 05:02:48 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_room_rj4(t_room *r)
{
	while(r && r->start != 1)
		r = r->next;
	r->by = 0;
	while(r && r->end != 1)
	{
			// ft_printf("{RED}%s %d %d\n", r->name, r->poids,r->by);
		if (r->by != 6 && r->by != 5 && r->by != 4 && r->tube->room->poids == 1)
		{
			r->by = 6;
			ft_printf("{RED}%s %d %d\n", r->name, r->poids,r->by);
			while(r->tube->room->by == 6  )
				r->tube = r->tube->next;
					r = r->tube->room;
		}
		else if(r->by == 6)	
			r->tube = r->tube->next;
		else 
			ft_exit("0");
	}
		ft_printf("{RED}%s %d End= %d\n\n", r->name, r->poids, r->end);
}

void	print_room_rj(t_room *r)
{
	while(r && r->start != 1)
		r = r->next;
	r->by = 0;
	while(r && r->end != 1)
	{
			// ft_printf("{RED}%s %d %d\n", r->name, r->poids,r->by);
		if (r->by != 4 && r->tube->room->poids == 1)
		{
			r->by = 4;
			ft_printf("{RED}%s %d %d\n", r->name, r->poids,r->by);
			while(r->tube->room->by == 4)
				r->tube = r->tube->next;
					r = r->tube->room;
		}
		else if(r->by == 4)	
			r->tube = r->tube->next;
		// else 
		// 	ft_exit("0");
	}
		ft_printf("{RED}%s %d End= %d\n\n", r->name, r->poids, r->end);
}

void	print_room_r(t_room *r)
{
	while(r && r->start != 1)
		r = r->next;
	r->by = 0;
	r->tube->room->poids = 1;
	while(r && r->end != 1)
	{
			ft_printf("{YEL}%s %d %d\n", r->name, r->poids,r->by);
		if (r->by != 5 && r->by != 4 && r->by != 6 && r->tube->room->poids == 1)
		{
			r->by = 4;
			ft_printf("{GRE}%s %d %d\n", r->name, r->poids,r->by);
			while(r->tube->room->by == 4 || r->tube->room->poids != 1)
			{
			ft_printf("{BLU}%s %d %d\n", r->tube->room->name, r->tube->room->poids,r->tube->room->by);
				r->tube = r->tube->next;
			}
			r = r->tube->room;
			ft_printf("{RED}%s %d %d\n", r->name, r->poids,r->by);

		}
		else  if(r->by == 4)
			// while(r->tube->prev)
			// 	r->tube = r->tube->prev;
			r->tube = r->tube->next;
	
		// else 
		// {
		// 	while(r->tube->prev)
		// 		r->tube = r->tube->prev;
		// }
		// ft_printf("{GRE}%s %d End= %d\n\n", r->name, r->poids, r->end);
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
			ft_printf("{RED}%s%s{%d}", "S=", r->name,r->dj);
		else if (r->end == 1)
			ft_printf("{RED}%s%s{%d}","E=", r->name,r->dj);
		else
			ft_printf("{GRE}%s{%d}", r->name, r->dj);
		if (r->tube == NULL)
			r = r->next;
		else
		{
			while (r->tube)
			{
					ft_printf("{YEL} - %s{%d}", r->tube->room->name, r->tube->room->dj);
					r->tube = r->tube->next;
			}
			r = r->next;
		}
		ft_printf("\n");
	}
}