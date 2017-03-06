/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djisktra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 06:51:53 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/05 06:52:03 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void put_(t_room *t, int i)
{
	// ft_printf("%s = %d = %d\n",t->name,t->dj,i);
	if(t->dj != 0)
		return ;
	t->dj = i;
}

void poids(t_room *r)
{
	int i;
	t_tube *tmp;
	i = 1;
	while(r->start != 1)
		r = r->next;
	r->dj = 1;
	while(r)
	{
		tmp = r->tube;
		while(r->tube)
		{
			put_(r->tube->room,r->dj + i);
			r->tube = r->tube->next;
		}
		if(!r->tube)
		r->tube = tmp;
		r = r->next;
	}
}