/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 08:18:05 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/17 21:52:19 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	reverse_list(t_path **list, t_ant *a)
{
	t_path	*p;
	t_path	*q;
	t_path	*r;

	p = *list;
	p->r->ants = a->ant;
	q = NULL;
	while (p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	a->n_end = q->name;
	*list = q;
}

int		check_link(t_room *r, char *s1)
{
	while (r)
	{
		if (!ft_strcmp(r->name, s1))
			return (0);
		r = r->next;
	}
	return (1);
}

void	verif(t_room *r)
{
	while (r)
	{
		if (r->poids == 1)
			r->poids = 0;
		if (r->poids == 1 && r->by != 4)
			r->poids = 0;
		// if (r->by == 4)
		// 	r->poids = 2;
		r = r->next;
	}
}

char	*next_comment(char *name, int *index)
{
	int	i;

	i = 0;
	while (*name == '#')
	{
		if (!ft_strcmp(name, "##start"))
			(*index) = 1;
		else if (!ft_strcmp(name, "##end"))
			(*index) = 2;
		get_next_line(0, &name);
	}
	while (name[i] && name[i] != ' ')
	{
		if (name[i] == '-')
			ft_exit("Room can't containt - further explication");
		i++;
	}
	if (*name == 'L' || *name == '#')
		ft_exit("Room can't start with L and #");
	return (name);
}

char	*ft_name_coord(char *name)
{
	char	*str;

	str = "NULL";
	str = *ft_strsplit(name, ' ');
	return (str);
}
