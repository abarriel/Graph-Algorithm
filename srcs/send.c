/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 03:03:25 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/07 03:03:27 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	one_path(t_path *p, t_ant *a)
{
	int i;
	int ants;

	ants = 1;
	i = 0;
	if (p->start == 1)
		p = p->next;
	while(p)
	{	
		ft_printf("L%d-%s ",a->ant,p->name);
		ants = p->ants;
		p = p->next;
		if(p)
		p->ants += ants;
	}
	ft_printf("\n");
}
void	handles_path(t_path **p, t_ant *a, int max_path)
{
	int i;
	int ants;

	ants = 1;
	i = 0;
	ft_printf("Nb ants = %d\nNb max_chemin = %d\n\n\n",a->ant, max_path);
	if (max_path == 1)
		one_path(*p,a);
}