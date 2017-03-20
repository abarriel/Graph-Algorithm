/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:27:42 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/20 05:44:54 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		multi_path(t_room *r, t_ant *a)
{
	int		tube;
	t_tube	*tmp;

	tube = 0;
	while (r && r->start != 1)
		r = r->next;
	tmp = r->tube;
	while (tmp)
	{
		if (tmp->room->end == 1)
			return (1);
		tmp = tmp->next;
		tube++;
	}
	if (a->ant < tube)
		tube = a->ant;
	return (tube);
}

int		check_stop(t_tube *r)
{
	t_tube *stop;

	stop = r;
	while (stop)
	{
		if (stop->room->by != 4 && stop->room->poids == 0)
			break ;
		stop = stop->next;
	}
	if (!stop)
		return (0);
	else
		return (1);
}

int		verif_no(t_room *tmp)
{
	t_tube	*ret;

	ret = tmp->tube;
	while (tmp->tube)
	{
		if (tmp->tube->room->poids != 2)
		{
			tmp->tube = ret;
			return (1);
		}
		tmp->tube = tmp->tube->next;
	}
	tmp->tube = NULL;
	return (0);
}
