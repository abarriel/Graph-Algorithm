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
	p->r->ants = a->ant;
	q = NULL;
	while (p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	// q->start = 2;
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
void 	sort_lists(t_path **p, int *max_path)
{
	int i;
	t_path **begin;
	t_path *tmp;


	i = 0;
	begin = p;
	tmp = NULL;
	while(i < *(max_path))
	{
		if (i + 1 < *(max_path) && (p[i]->size > p[i + 1]->size))
		{
			tmp = p[i];
			p[i] = p[i + 1];
			p[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
	i = 0;
	p = begin;
	// while(i < *(max_path))
	// {
	// 	if (i + 1 < *(max_path) && (p[i + 1]->size > (p[0]->size + 2)))
	// 	{
	// 		*(max_path) = i + 1;
	// 		p[i + 1] = NULL;
	// 		p = begin;
	// 		return ;
	// 		// free(p[i + 1]);
	// 		// i = 0;
	// 	}
	// 	i++;
	// }
	// // p = begin;
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
	// if (max_path > 1)
	// sort_lists(p,&max_path);
	// i = 0;
	// ft_printf("\n\n");
	// while(i <= max_path)
	// {
	// 	tmp[i] = p[i];
	// 	i++;
	// }
	i = 0;
	ft_printf("%d",max_path);	
	while (end != a->ant)
	{
		while (i < max_path)
		{
			while (p[i])
			{
			// ft_printf("#%d#",end); QUAND START ET END COLER C LE BORDEL JAI REPAERE LE END CAR IL SINCRIMENTER AVEC LE NOMBRE DE FOURMI ALORS QUE C NB DE FOI QUNE FOURMIS ET ARRIVER A END
			// 	if (p[i]->r->end == 1 && p[i]->next->r->ants > 0 && p[i]->next->r->start != 1)
			// 	{
			// 		// p[i]->r->ants++;
			// 		p[i]->r->ants = p[i]->next->r->ants;
			// 		p[i]->next->r->ants =0;
			// 		print_ants(a->bonus_color, p[i]->r->ants,p[i]->name);
			// 		end++;
			// // ft_printf("{%d}",end);
			// 		if (end == a->ant)
			// 			return ;
			// 	}
				if (p[i]->next && p[i]->next->r->start == 1 && start > 0)
				{
					p[i]->next->r->ants--;
					start--;
					ants++;
					p[i]->r->ants = ants;
						if(p[i]->r->end == 1)
						end++;
			// ft_printf("(%d)",end);
					print_ants(a->bonus_color, p[i]->r->ants,p[i]->name);
				}
				else if (p[i]->next && p[i]->next->r->ants > 0 && p[i]->next->r->start != 1)
				{

					p[i]->r->ants = p[i]->next->r->ants;
					p[i]->next->r->ants = 0;
					print_ants(a->bonus_color, p[i]->r->ants,p[i]->name);
					if(p[i]->r->end == 1)
						end++;
				}
				p[i] = p[i]->next;
				if(end == a->ant)
				return ;
			}
			p[i] = tmp[i];
				if (p[i]->r->start == 1 && p[i]->next->r->end == 1)
					end++;
			i++;
			// ft_printf("[%d]",end);
			if(end == a->ant)
				return ;
		}
		i = 0;
		ft_printf("\n");
		p[i] = tmp[i];
	}
}
