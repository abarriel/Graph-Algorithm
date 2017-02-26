/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:52:46 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/23 16:52:47 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room *recur_algo(t_room *r, char *name)
{
	// ft_printf("{YEL}%s \n",r->tube->room->name);

	// if (ft_strcmp(r->tube->room->name, name) == 0)
	// 	{
	// 		// ft_printf("%s\n",r->tube->room->name);
	// 		if (r->tube->next)
	// 		{
	// 			r->tube = r->tube->next;
	// 			r = r->tube->room;
	// 		}
	// 	}
	// else
	// 	r = r->tube->room;
	return(r);
}
int start_algo(t_room *r, t_ant *a)
{
	// while(r)
	// {
	// 	ft_printf("Finder %p poids:[%d] %s\n",r,r->poids,r->name);
	// 	if (r->end == 1)
	// 	{
	// 		ft_printf("Toucher la fin %p %s\n",r,r->name);
	// 		exit(1);
	// 	}
	// 	if(r->poids == -1)
	// 	{
	// 		if(r->tube->next)
	// 			r->tube =  r->tube->next;
	// 	}
	// 	if (r->tube->room)
	// 	{
	//
	// 	r->poids = -1;
	// 	r = r->tube->room;
	// 	}
	// }
	// recur_algo(r);
	// char *name;
	// int index = 0;
	//
	// while(index < 10)
	// {
		// name = r->name;
		// ft_printf("{BLU}%s - ",name);
		// r = r->tube->room;
		// ft_printf("{BLU}-%s",name);

	// 	r = recur_algo(r,name);
	// 	index++;
	// }
	// while(r && r->end != 1)
	// {
	//
	// r->name = "d";
	// r->name = "ddd";
	// r->poids = 2016;
			// ft_printf("%p %s\n",r, r->name);
			// r = r->tube->room;
			// r->poids = 10;
			// ft_printf("%p %s %d\n",r, r->name,r->poids);
			// r = r->tube->room;
			// ft_printf("%p %s %d\n",r, r->name,r->poids);
			// r = r->tube->room;
			// ft_printf("%p %s %d\n",r, r->name,r->poids);
			// r->tube = r->tube->next;
			// r = r->tube->room;
			// ft_printf("%p %s %d\n",r, r->name,r->poids);
			// r = r->tube->room;
			// ft_printf("%p %s %d\n",r, r->name,r->poids);
			// ft_printf("%p %s %d\n",r, r->name, r->poids);
			// r = r->next;
			// ft_printf("[%s]\n",r->name);

			// r->poids = 1;

	// 	r = recur_algo(r);
	// }
	// 	ft_printf("%s\n",r->name);
	// while(r && r->start != 1)
	// 	r = r->next;
	// ft_printf("%s\n",r->name);
	// while (r && r->end != 1)
	// {
	// 	if (r->tube->previous == 1)
	// 	{
	// 		return(0);
	// 		r->tube = r->tube->next;
	// 	}
	// 	r = r->tube->room;``
	// 	ft_printf("%s\n",r->name);
	// }
	// 	r = r->tube->room;
	// 	ft_printf("%s",r->name);
	// 	r = r->tube->room;
	// 	if (r->tube->room->name == '1')
	// 		r->tube = r->tube->next;
	// 	ft_printf("%s",r->name);
	// // 	r = r->tube->room;
	// // 	ft_printf("%s",r->name);
	// // 	// r = r->tube->room;
	// 	r = r->next;
	// }
	print_room(r);
	return 0;
}
