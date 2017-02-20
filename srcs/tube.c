/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 13:27:03 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/20 13:27:04 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int 	parse_error_tube(int index, char *n)
{
	static int u = 0;

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
   t_tube *u;

   if(!(u = (t_tube*)malloc(sizeof(t_tube))))
	   ft_exit("Failed to Malloc");
   u->name = r->name;
   u->room = r;
   u->next = NULL;
   return(u);
}

void 	add_back_tube(t_tube **t, t_room *start_r)
{
	t_tube	*tmp;

	tmp = *t;
	if(!tmp)
	{
		*t = init_tube(start_r);
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = init_tube(start_r);
}

int check_tube(t_room **r, t_room *rt, char *line, int index)
{
	t_tube *u;
	t_room *start_r;

	start_r = *r;
	// ft_printf("{RED}{%s}\n",rt->name);
	line = ft_strsub(line, index + 1, ft_strlen(line) - (index + 1));
	while(start_r)
	{
		if(!ft_strcmp(line,start_r->name))
			{
				add_back_tube(&rt->tube,start_r);
				// ft_printf("%s\n",rt->tube->room->name);
				// return(0);
			}
		start_r = start_r->next;
	}
	return (0);
}
int add_tube(t_room **r, char *line, int index)
{
	t_room *rt;

	rt = *r;
	while(rt)
	{
		if(!ft_strncmp(line,rt->name,index))
		{
			check_tube(r, rt, line, index);
			// ft_printf("[%s]\n",rt->tube->room->name);
		}
		rt = rt->next;
	}
	// ft_printf("[%s]\n",(*r)->tube->room->name);
	return(0);
}
