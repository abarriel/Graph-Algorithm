/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:33:15 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/22 00:20:20 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		dashi(char *line)
{
	int i;
	int dash;

	dash = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
			dash++;
		i++;
	}
	if (dash != 1)
		return (0);
	return (1);
}

void	check_room(t_room *tmp)
{
	t_room	*begin_list;
	int		i;
	int		u;

	i = 0;
	u = 0;
	begin_list = tmp;
	while (tmp)
	{
		if (tmp->start == 1)
			u++;
		if (tmp->end == 1)
			i++;
		tmp = tmp->next;
	}
	if (u != 1)
		ft_exit("Missing Start");
	if (i != 1)
		ft_exit("Missing End");
	tmp = begin_list;
}

int		check_stopping(t_room *tmp, char *line, int index)
{
	t_room	*begin_list;
	int		u;

	begin_list = tmp;
	u = 0;
	while (tmp)
	{
		if (!ft_strncmp(line, tmp->name, index))
			u++;
		tmp = tmp->next;
	}
	tmp = begin_list;
	if (u == 0)
		return (1);
	return (0);
}

void	parser(int bp, int bc, char *line)
{
	static t_room		*r = NULL;
	t_ant				*a;
	static int			stop = 0;

	(get_next_line(0, &line)) ? NULL : ft_exit("Empty");
	a = init_ant(line, bp, bc);
	while (get_next_line(0, &line) > 0)
	{
		if (*line != '#' && (if_so_('-', line)))
		{
			stop = 1;
			if ((add_tube(&r, line)))
				break ;
		}
		else if (!ft_strcmp("##start", line) && stop == 0)
			add_back_room(&r, line, 1);
		else if (!ft_strcmp("##end", line) && stop == 0)
			add_back_room(&r, line, 2);
		else if (stop == 0)
			add_back_room(&r, line, 0);
		else if (*line != '#')
			break ;
	}
	(stop == 0) ? ft_exit("No tube") : NULL;
	handles_algo(r, a);
}
