/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:32:52 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/19 11:32:54 by abarriel         ###   ########.fr       */
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

t_ant	*init_ant(char *name)
{
	t_ant	*r;
	int		i;

	if (!(i = ft_atoi(name)) || !name)
		ft_exit("Setting up failed bc missing value or Empty files");
	if (!(r = (t_ant*)malloc(sizeof(t_ant))))
		ft_exit("Failed to Malloc");
 	r->ant = i;
	r->next = NULL;
	return(r);

}

t_tube	*init_tube(void)
{
	t_tube *r;

	if(!(r = (t_tube*)malloc(sizeof(t_tube))))
		ft_exit("Failed to Malloc");
	r->room = NULL;
	r->next = NULL;
	return(r);
}

int		main(void)
{
	parser();
	return (0);
}
