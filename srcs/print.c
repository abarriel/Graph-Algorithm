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

void	print_room_rj(t_room *r)
{
	t_room *tmp;
	while(r && r->start != 1)
		r = r->next;
	r->by = 0;
	while(r && r->end != 1)
	{
			// ft_printf("{RED}%s %d %d\n", r->name, r->poids,r->by);
		if (r->by != 5 && r->by != 4 && r->tube->room->poids == 1)
		{
			r->by = 5;
			ft_printf("{RED}%s %d %d\n", r->name, r->poids,r->by);
			// ft_printf("{GRE}%s %d\n", r->name, r->poids);
			while(r->tube->room->by == 5  )
				r->tube = r->tube->next;
					r = r->tube->room;
		}
		else if(r->by == 5)	
			r->tube = r->tube->next;
	}
		ft_printf("{RED}%s %d End= %d\n", r->name, r->poids, r->end);

	// while (r)
	// {
	// 	// if (r->poids == 1)
	// 	// 	ft_printf("{GRE}%s  %d\n", r->name, r->end);
	// 	r = r->next;
	// }
}

void	print_room_r(t_room *r)
{
	t_room *tmp;
	while(r && r->start != 1)
		r = r->next;
	r->by = 0;
	while(r && r->end != 1)
	{
			// ft_printf("{RED}%s %d %d\n", r->name, r->poids,r->by);
		if (r->by != 4 && r->tube->room->poids == 1)
		{
			r->by = 4;
			ft_printf("{GRE}%s %d %d\n", r->name, r->poids,r->by);
			// ft_printf("{GRE}%s %d\n", r->name, r->poids);
			while(r->tube->room->by == 4)
				r->tube = r->tube->next;
					r = r->tube->room;
		}
		else if(r->by == 4)	
			r->tube = r->tube->next;
	}
		ft_printf("{GRE}%s %d End= %d\n\n", r->name, r->poids, r->end);

	// while (r)
	// {
	// 	// if (r->poids == 1)
	// 	// 	ft_printf("{GRE}%s  %d\n", r->name, r->end);
	// 	r = r->next;
	// }
}

void	print_room(t_room *r)
{
	while (r)
	{
		if (r->start == 1)
			ft_printf("{RED}%s%s", r->name, " = Start");
		else if (r->end == 1)
			ft_printf("{RED}%s%s", r->name, " = End");
		else
			ft_printf("{GRE}%s", r->name);
		if (r->tube == NULL)
			r = r->next;
		else
		{
			while (r->tube)
			{
					ft_printf("{YEL} - %s", r->tube->room->name);
					if (r->tube->prev)
					ft_printf("{BLU} - %s", r->tube->prev->room->name);
					r->tube = r->tube->next;
				}
			r = r->next;
		}
		ft_printf("\n");
	}
}