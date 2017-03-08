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
ft_putstr_fd(RED, fd);
	if (color_nfun == 2)
		ft_putstr_fd(GREEN, fd);
	if (color_nfun == 3)
		ft_putstr_fd(BLUE, fd);
	if (color_nfun == 4)
		ft_putstr_fd(PURPLE, fd);
	if (color_nfun == 5)
		ft_putstr_fd(YELLOW, fd);
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
		ft_printf("{GRE}%d\n",p[i]->ants);
		while(i < max_path)
		{
			while(p[i])
			{
				if (p[i]->start == 2 && p[i]->next->ants > 0)
				{
					end++;
					p[i]->ants = end;
					ft_putstr("0;[")
					ft_printf("L%d-%s ",p[i]->ants,p[i]->name);
					if (end == a->ant)
						return ;
					// if(p[i]->ants == a->ant)
					// 	return;
				}
				else if (p[i]->next && p[i]->next->start == 1 && start > 0)
				{
					p[i]->next->ants--;
					start--;
					ants++;
					p[i]->ants = ants;
					ft_printf("L%d-%s ",p[i]->ants,p[i]->name);
				}
				else if (p[i]->next && p[i]->next->ants > 0 && p[i]->next->start != 1)
				{
					p[i]->ants = p[i]->next->ants;
					p[i]->next->ants = 0;
					ft_printf("L%d-%s ",p[i]->ants,p[i]->name);
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
