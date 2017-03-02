/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:52:46 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/01 02:37:15 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int 	handles_algo(t_room *r)
{
	if (r->tube->room->poids == 1)
	{
		if (r->tube->next)
			r->tube = r->tube->next;
		else
			r->poids = 2;
	}
	r = r->tube->room;
	start_algo(r, NULL);
	return 0;

}

t_tube	*new_list(t_tube **r)
{
	t_tube *begin_list;
	t_tube *final;

	begin_list = *r;
	final = *r;
	while (final)
	{
		ft_printf("%s\n",final->name);
		final = final->next;
	}
		final = begin_list;
		return (final);
}

int		start_algo(t_room *r, t_ant *a)
{
	static t_room *rmp;
	t_tube *tmp;

	tmp = new_list(&r->tube);
	if(!rmp)
		rmp = r;
	if (r && r->poids != 2)
	{
		r->poids = 1;
		ft_printf("{GRE}[%s] - [%d]\n", r->name, r->poids);
		// tmp = new_list(&r->tube);
		handles_algo(r);
	}
	else if (r->poids == 2)
	{
		ft_printf("{GRE}Rentre a=[%s] - [%d]\n", r->name, r->poids);
		ft_printf("{BLU}1erMaillon = [%s] - [%d]\n", tmp->name, tmp->poids);
			// tmp =	new_list(&r->tube);
		// tmp = r->tube->room;
		r = r->tube->room;
		// ft_printf("{YEL}Apres =[%s] - [%d]\n", r->name, r->poids);
		while(r->tube && r->tube->room->poids == 2)
		{
			ft_printf("{PUR}Dedans tube[%s] - [%d]\n", r->tube->room->name, r->tube->room->poids);
			if(r->tube->room->poids != 2)
			{
				r = r->tube->room;
				// ft_printf("U\n");
					break;
			}
			r->tube = r->tube->next;
		}
		ft_printf("{YEL}New r[%s] - [%d]\n", r->name, r->poids);
			// ft_exit("ok");
		// ft_printf("{PUR}Sorti tube[%s] - [%d]\n", tmp->tube->room->name, tmp->tube->room->poids);
		if (r->tube)
			r = r->tube->room;
		else
		{
				r->poids = 2;
			ft_exit("Bug ou OK");
		}
		// ft_printf("{YEL}New r[%s] - [%d]\n", r->name, r->poids);
		// ft_printf("D\n");
		// ft_printf("{PUR}r->tube[%s] - [%d]\n", r->tube->room->name, r->tube->room->poids);

		// exit(1);
		// if(r->tube->room->poids == 1)
		// {
		// 	// if(!r->tube->room->next)

		// 	// ft_printf("{PUR}[%s] - [%d]\n", r->tube->room->next->name, r->tube->room->next->poids);
		// }		// while(r->tube)
		// // {
			// ft_printf("{PUR}[%s] - [%d]\n", r->tube->room->name, r->tube->room->poids);
		// 	r->tube = r->tube->next;
		// }

		// Sft_exit("dd");
		ft_printf("{RED}Sort a [%s] - [%d]\n", r->name, r->poids);
		// r = rmp;
		handles_algo(r);
		
		// start_algo(r,a);
	}
	return (0);
}

// int 	handles_algo(t_room *r)
// {
// 	if (r->tube->room->poids == 1 || r->tube->room->poids == 3)
// 	{
// 		if (r->tube->next)
// 		r->tube = r->tube->next;
// 		else
// 		r->tube->room->poids = 2;
// 	}
// 	if (r->tube->room->poids == 2)
// 	{
// 		// r = r->tube->room;
// 		r->tube->room->poids = 2;
// 		r->end = 1;
// 	}
// 	else 
// 	r = r->tube->room;
// 	start_algo(r, NULL);
// 	return 0;

// }
// int		start_algo(t_room *r, t_ant *a)
// {
// 	static t_room *rmp;
// 	t_tube *tmp;

// 	if(!rmp)
// 		rmp = r;
// 	if (r && r->end != 1)
// 	{
// 	r->poids = 1;
// 		ft_printf("{GRE}[%s] - [%d]\n", r->name, r->poids);
// 		handles_algo(r);
// 	}
// 	else
// 	{
// 		r->poids = 3;
// 		ft_printf("{RED}[%s] - [%d]\n", r->name, r->poids);
// 		if (r->tube->room->poids == 1)
// 		{
// 		if (r->tube->next)
// 		r->tube = r->tube->next;
// 		}
// 		r = r->tube->room;
// 		handles_algo(r);
		
// 		// start_algo(r,a);
// 	}
// 	return (0);
// }
