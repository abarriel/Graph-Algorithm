/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 05:02:47 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/11 08:03:44 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_path(t_path *path)
{
	if (!path)
		return ;
	while (path)
	{
		ft_printf("%s", path->name);
		if (path->next)
			ft_printf("->");
		path = path->next;
	}
	ft_printf("\n\n");
}

void	print_room(t_room *r1)
{
	t_room *r;

	r = r1;
	while (r)
	{
		if (r->start == 1)
			ft_printf("{RED}[%s{%s b:%d p:%d}", "S=", r->name, r->by, r->end);
		else if (r->end == 1)
			ft_printf("{RED}[%s{%s b:%d p:%d", "E=", r->name, r->by, r->end);
		else
			ft_printf("{GRE}[%s b:%d p:%d}", r->name, r->by, r->poids);
		if (r->tube == NULL)
			r = r->next;
		else
		{
			while (r->tube)
			{
				ft_printf("{YEL} - {%s b:%d p:%d}", r->tube->room->name,
						r->tube->room->by, r->tube->room->poids);
				r->tube = r->tube->next;
			}
			r = r->next;
		}
		ft_printf("\n");
	}
}
