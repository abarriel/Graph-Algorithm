/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 03:03:25 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/08 11:28:02 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	reverse_list(t_path **list, t_ant *a)
{
	t_path	*p;
	t_path	*q;
	t_path	*r;

	p = *list;
	p->ants = a->ant;
	q = NULL;
	while (p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	q->start = 2;
	*list = q;
}

void 	print_ants(int bc, int ants, char *name)
{
	int i;

	i = 1;
	if (bc == 0)
	{
		ft_printf("L%d-%s ", ants, name);
		return ;
	}
	i = ants;
	if (ants > 256)
		i = ants - 256;	
	ft_putstr("\e[38;5;");
	ft_putnbr(i);
	ft_putstr("m");
	ft_printf("L%d-%s ", ants, name);
	ft_putstr(RESET);
}

void	handles_path(t_path **p, t_ant *a, int max_path)
{
	int i;
	int ants;
	int end;
	int start;

	t_path **tmp;
	end = 0;
	tmp = NULL;
	ants = 0;
	i = 0;
	start = a->ant;
	tmp = (t_path**)malloc(sizeof(t_path) * max_path);
	while(i < max_path)
	{	
		reverse_list(&p[i],a);
		tmp[i] = p[i];
		i++;
	}
	i = 0;
	while(end <= a->ant)
	{
		while(i < max_path)
		{
			while(p[i])
			{
				if (p[i]->start == 2 && p[i]->next->ants > 0)
				{
					end++;
					p[i]->ants = end;
					print_ants(a->bonus_color, p[i]->ants,p[i]->name);
					if (end == a->ant)
						return ;
				}
				else if (p[i]->next && p[i]->next->start == 1 && start > 0)
				{
					p[i]->next->ants--;
					start--;
					ants++;
					p[i]->ants = ants;
					print_ants(a->bonus_color, p[i]->ants,p[i]->name);
				}
				else if (p[i]->next && p[i]->next->ants > 0 && p[i]->next->start != 1)
				{
					p[i]->ants = p[i]->next->ants;
					p[i]->next->ants = 0;
					print_ants(a->bonus_color, p[i]->ants,p[i]->name);
				}
				p[i] = p[i]->next;
			}
			p[i] = tmp[i];
			i++;
		}
		
		i = 0;
		ft_printf("\n");
		p[i] = tmp[i];
		// i++;
	}
}
