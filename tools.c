/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 15:55:02 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/19 15:55:03 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int 	parse_error_room(int index, char *n)
{
	static int u = 0;

	if (*n == '#')
		return (0);
	if (u == 2 && index == 2)
		ft_exit("Plusieur End");
	if (u == 1 && index == 1)
		ft_exit("Plusieur Start");
	// if (!(ft_isdigit(*n)))
	// 	ft_exit("ERROR");
	u = (index == 2) ? 2 : u;
	u = (index == 1) ? 1 : u;
	return (1);
}
void 	add_back_room(t_room **r, char *name, int index)
{
	t_room	*tmp;

	if (!(parse_error_room(index, name)))
		return ;
	tmp = *r;
	if(!tmp)
	{
		*r = init_room(name, index);
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = init_room(name, index);
}

int 	parse_error_tube(int index, char *n)
{
	static int u = 0;

	if (*n == '#')
		return (0);
	if (u == 2 && index == 2)
		ft_exit("Plusieur End");
	if (u == 1 && index == 1)
		ft_exit("Plusieur Start");
	if (!(ft_isdigit(*n)))
		ft_exit("ERROR");
	u = (index == 2) ? 2 : u;
	u = (index == 1) ? 1 : u;
	return (1);
}

void 	add_back_tube(t_tube **t, char *name, int index)
{
	t_tube	*tmp;

	// if (!(parse_error_tube(index, name)))
	// 	return ;
	tmp = *t;
	if(!tmp)
	{
		*t = init_tube();
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = init_tube();
}
