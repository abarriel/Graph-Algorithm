/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 08:18:05 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/11 10:14:53 by abarriel         ###   ########.fr       */
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
		if (r->poids == 1 && r->by != 4)
			r->poids = 0;
		r = r->next;
	}
}

char	*next_comment(char *name)
{
	while (*name == '#')
		get_next_line(0, &name);
	if (ft_strchr(name, '-'))
		ft_exit("Room can't containt - further explication");
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
