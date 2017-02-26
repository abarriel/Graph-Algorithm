/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 13:27:03 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/23 17:58:31 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		parse_error_tube(int index, char *n)
{
	static int	u = 0;

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

t_tube	*init_tube(t_room *r, int previous)
{
	t_tube	*u;

	if (!(u = (t_tube*)malloc(sizeof(t_tube))))
		ft_exit("Failed to Malloc");
	if (r != NULL)
	{
		u->name = r->name;
		u->room = r;
	}
	else
	{
		u->name = "Test";
		u->room = NULL;
	}
	u->previous = previous;
	u->poids = 0;
	u->next = NULL;
	return (u);
}

void	add_back_tube(t_tube **t, t_room *start_r, int previous)
{
	t_tube	*tmp;

	tmp = *t;
	if (!tmp)
	{
		*t = init_tube(start_r, previous);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_tube(start_r, previous);
}

int		check_tube(t_room *tmp1, t_room *tmp, char *line, int index)
{
	int		stop;

	stop = check_stopping(tmp1, line, ft_strlen(line));
	while (tmp1 && stop != 1)
	{
		if (!ft_strcmp(line, tmp1->name))
		{
			add_back_tube(&tmp->tube, tmp1, 0);
			add_back_tube(&tmp1->tube, tmp, 1);
		}
		tmp1 = tmp1->next;
	}
	return (stop);
}

int		add_tube(t_room **r, char *line, int index)
{
	t_room	*tmp;
	t_room	*tmp1;
	char	**s;
	int		stop;

	tmp = *r;
	check_room(tmp);
	tmp1 = tmp;
	s = ft_strsplit(line,'-');
	stop = check_stopping(tmp, line, index);
	while (tmp && stop != 1)
	{
		if (!ft_strcmp(s[0], tmp->name))
			stop = check_tube(tmp1, tmp, s[1], index);
		tmp = tmp->next;
	}
	return (stop);
}
