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

int check_tube(t_room *tmp1,t_room *tmp, char *line, int index)
{
	line = ft_strsub(line, index + 1, ft_strlen(line) - (index + 1));
	// ft_printf("{GRE}%s - ",tmp->name);
	while(tmp1)
	{
		if(!ft_strcmp(line,tmp1->name))
		{
			add_back_tube(&tmp->tube,tmp1);
			add_back_tube(&tmp1->tube,tmp);

		}
		// else
		// 	add_back_tube(&tmp->tube,NULL);
		// PAS OUBLIER DE ELSE SI LE TUBE POINT SUR UN ENDROIT INCONNU ALORS ON ARRETE DE RECUPERER LES INFO
		// ET AVEC CE QUON A ON ESSAYE DE TRACE UN CHEMIN, PAS OUBLEIR
		tmp1 = tmp1->next;
	}
	return (0);
}

int add_tube(t_room **r, char *line, int index)
{
	t_room *tmp;
	t_room *tmp1;
	char *s;

	tmp = *r;
	tmp1 = tmp;
	while (tmp)
	{
		if(!ft_strncmp(line,tmp->name,index))
			check_tube(tmp1, tmp, line, index);
		tmp = tmp->next;
	}
	return(0);
}
