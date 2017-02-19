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
	t_tube 	*u;
	t_ant 	*a;

	get_next_line(0, &line);
	a = init_ant(line);
	while (get_next_line(0, &line) > 0)
	{
		if (*line != '#' && if_so('-',line))
			break ;
		if (ft_strcmp("##start", line) == 0 && get_next_line(0, &line) == 1)
				add_back_room(&r,line, 1);
		else if (ft_strcmp("##end", line) == 0 && get_next_line(0, &line) == 1)
				add_back_room(&r,line, 2);
		else
				add_back_room(&r, line, 0);
	}
	while (get_next_line(0, &line) > 0)
			add_back_tube(&u, line, 0);
	while (r)
	{
		if (r->start == 1)
		ft_printf("{GRE}%s%s\n",r->name, " = Start");
		else if (r->end == 1)
		ft_printf("{GRE}%s%s\n",r->name, " = End");
		else
		ft_printf("{GRE}%s\n", r->name);
		r = r->next;
	}
	// while (u)
	// {
	// 	ft_printf("{RED}%s\n", u->name);
	// 	u = u->next;
	// }
	return (0);
}
