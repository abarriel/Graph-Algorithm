/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 13:27:03 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/20 09:09:28 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_tube	*init_tube(t_room *r)
{
	t_tube	*u;

	if (!(u = (t_tube*)malloc(sizeof(t_tube))))
		ft_exit("Failed to Malloc");
	u->room = r;
	u->next = NULL;
	return (u);
}

void	add_back_tube(t_tube **t, t_room *start_r)
{
	t_tube	*tmp;
	t_tube	*prev;

	tmp = *t;
	if (!tmp)
	{
		*t = init_tube(start_r);
		(*t)->prev = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	prev = tmp;
	tmp->next = init_tube(start_r);
	tmp = tmp->next;
	tmp->prev = prev;
}

int		check_tube(t_room *tmp1, t_room *tmp, char *line)
{
	int		stop;

	stop = check_stopping(tmp1, line, ft_strlen(line));
	while (tmp1 && stop != 1)
	{
		if (!ft_strcmp(line, tmp1->name))
		{
			add_back_tube(&tmp->tube, tmp1);
			add_back_tube(&tmp1->tube, tmp);
		}
		tmp1 = tmp1->next;
	}
	return (stop);
}

int		add_tube(t_room **r, char *line)
{
	t_room	*tmp;
	t_room	*tmp1;
	char	**s;
	int		stop;

	tmp = *r;
	stop = 0;
	check_room(tmp);
	tmp1 = tmp;
	s = ft_strsplit(line, '-');
	if (!s[1] || !s[0] || !(dashi(line)))
		return (1);
	stop = check_link(*r, s[0]);
	stop += check_link(*r, s[1]);
	while (tmp && stop != 1)
	{
		if (!ft_strcmp(s[0], tmp->name))
			stop = check_tube(tmp1, tmp, s[1]);
		tmp = tmp->next;
	}
	free_split(s);
	ft_strdel(&line);
	return (stop);
}
