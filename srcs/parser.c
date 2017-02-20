/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:33:15 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/19 11:33:16 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		parser(void)
{
	char	*line;
	t_room 	*r;
	t_ant 	*a;
	int 	i;

	i = 0;
	get_next_line(0, &line);
	a = init_ant(line);
	while (get_next_line(0, &line) > 0)
	{
		if (*line != '#' &&  (i = if_so('-',line)))
			add_tube(&r, line, i);
		else if (ft_strcmp("##start", line) == 0 && get_next_line(0, &line) == 1)
				add_back_room(&r,line, 1);
		else if (ft_strcmp("##end", line) == 0 && get_next_line(0, &line) == 1)
				add_back_room(&r,line, 2);
		else
				add_back_room(&r, line, 0);
	}
	// ft_printf("%s",r->tube->name);
	while (r)
	{
		if (r->start == 1)
		ft_printf("{GRE}%s%s",r->name, " = Start");
		else if (r->end == 1)
		ft_printf("{GRE}%s%s",r->name, " = End");
		else
		ft_printf("{GRE}%s", r->name);
		// if(r->tube->room)
		// ft_printf("{RED} = %s", r->tube->room->name);
		ft_printf("\n");
		r = r->next;
	}
	return (0);
}
