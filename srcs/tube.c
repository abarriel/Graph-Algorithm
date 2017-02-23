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

t_tube	*init_tube(t_room *r)
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
		u->name = "Tes";
		u->room = NULL;
	}
	u->next = NULL;
	return (u);
}

void	add_back_tube(t_tube **t, t_room *start_r)
{
	t_tube	*tmp;

	tmp = *t;
	if (!tmp)
	{
		*t = init_tube(start_r);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_tube(start_r);
}

int		check_tube(t_room *tmp1, t_room *tmp, char *line, int index)
{
	int		stop;

	line = ft_strsub(line, index + 1, ft_strlen(line) - (index + 1));
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

int		add_tube(t_room **r, char *line, int index)
{
	t_room	*tmp;
	t_room	*tmp1;
	char	*s;
	int		stop;

	tmp = *r;
	check_room(tmp);
	tmp1 = tmp;
	stop = check_stopping(tmp, line, index);
	while (tmp && stop != 1)
	{
		if (!ft_strncmp(line, tmp->name, index))
			stop = check_tube(tmp1, tmp, line, index);
		tmp = tmp->next;
	}
	return (stop);
}
