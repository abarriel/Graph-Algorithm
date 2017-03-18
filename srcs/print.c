/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 05:02:47 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/18 22:59:41 by abarriel         ###   ########.fr       */
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
	t_room	*r;

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

void	print_ants(t_ant *a, int ants, char *name)
{
	int	i;

	i = 1;
	if (a->bonus_color == 0)
	{
		ft_printf("L%d-%s", ants, name);
		if ((a->end + 1 == a->ant) && !ft_strcmp(name, a->n_end))
			return ;
		ft_putchar(' ');
		return ;
	}
	i = ants;
	if (ants > 256)
		i = ants - 256;
	if (i == 16)
		i = 2;
	ft_putstr("\e[38;5;");
	ft_putnbr(i);
	ft_putstr("m");
	ft_printf("L%d-%s", ants, name);
	ft_putstr(RESET);
	if ((a->end + 1 == a->ant) && !ft_strcmp(name, a->n_end))
		return ;
	ft_putchar(' ');
}
