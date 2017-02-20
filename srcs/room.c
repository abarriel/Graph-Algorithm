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

char	*ft_name_coord(char *name)
{
	char *str;

	str = "NULL";
	str = *ft_strsplit(name,' ');
	// if (!(ft_strchr(name, '-')))
	// 	ft_exit("Name with -");
	return(str);
}

t_room	*init_room(char *name, int index)
{
	t_room	*r;

	if(!(r = (t_room*)malloc(sizeof(t_room))))
		ft_exit("Failed to Malloc");
	r->tube = NULL;
	r->next = NULL;
	r->name = ft_name_coord(name);
	r->start = (index == 1) ? 1 : 0;
	r->end = (index == 2) ? 1 : 0;
	return(r);

}

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
