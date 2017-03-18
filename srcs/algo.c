/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:52:46 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/18 02:37:12 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	algo_lem3(t_room **r, t_tube *tmp, t_room *begin, t_room *debut)
{
	while((*r)->tube->prev)
		(*r)->tube = (*r)->tube->prev;
	while((*r)->tube && (*r)->tube->room->poids != 0)
			(*r)->tube = (*r)->tube->next;
	if (!(*r)->tube)
 	{
 		(*r)->poids = 2;
 		verif(begin);
 		(*r) = debut;
 	}
}

int		algo_lem2(t_room **r, t_tube **tmp, t_room *begin, t_room *debut)
{
	if((*r)->tube == NULL)
			return (0);
	if ((*r)->tube->room->poids == 0)
	{
		(*r)->tube->room->poids = 1;
		(*r) = (*r)->tube->room;
	}
	else
	{
		algo_lem3(r, (*tmp), begin, debut );
	}
	return (1);
}

void	algo_lem(t_room *r)
{
	t_tube	*tmp;
	t_room	*begin;
	t_room	*debut;

	begin = r;
	while (r->start != 1 && r)
		r = r->next;
	r->poids = 1 ;
	debut = r;
	while (r->end != 1)
	{
			if(!algo_lem2(&r,&tmp,begin,debut))
			return ;
	}
	return ;
}

void	handles_algo(t_room *r, t_ant *a)
{
	t_path	**path;
	int		i;
	int		b;
	int		j;

	i = 0;
	b = -1;
	if (!(j = multi_path(r, a)))
		ft_exit("Invalid Path");
	path = (t_path **)malloc(sizeof(t_path *) * j);
	// print_room(r);
	// while (i == 0 && ++b < j)
	// {
		algo_lem(r);
		path[b]= save_path(r, &i);
		print_path(path[b]);
		algo_lem(r);
		// print_room(r);
		path[b]= save_path(r, &i);
		print_path(path[b]);


		// algo_lem(r);
	// 	if (!path[b])
	// 	{
	// 		j = b;
	// 		break ;
	// 	}
	// 	else if (a->bonus_path == 1)
	// }
	// if (!(path[0]))
	// 	ft_exit("Invalid Path");
	// handles_path(path, a, j);
}
