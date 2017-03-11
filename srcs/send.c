/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 03:03:25 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/11 10:15:49 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	erase_large_path(t_path **p, t_path **begin, int *max_path)
{
	int	i;

	i = 0;
	while (i < *(max_path))
	{
		if (i + 1 < *(max_path) && (p[i + 1]->size > (p[0]->size + 1)))
		{
			*(max_path) = i + 1;
			p[i + 1] = NULL;
			p = begin;
			return ;
		}
		i++;
	}
	p = begin;
}

void	sort_multi_path(t_path **p, int *max_path)
{
	int		i;
	t_path	**begin;
	t_path	*tmp;

	i = 0;
	begin = p;
	tmp = NULL;
	while (i < *(max_path))
	{
		if (i + 1 < *(max_path) && (p[i]->size > p[i + 1]->size))
		{
			tmp = p[i];
			p[i] = p[i + 1];
			p[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
	p = begin;
	erase_large_path(p, begin, max_path);
}

void	handles_path_(t_path **tmp, int *ii, t_path **p, t_ant *a)
{
	int	i;

	i = (*ii);
	while (p[i])
	{
		if (p[i]->next && p[i]->next->r->start == 1 && a->start > 0)
		{
			p[i]->next->r->ants--;
			a->start--;
			a->dant++;
			p[i]->r->ants = a->dant;
			a->end += (p[i]->r->end == 1) ? 1 : 0;
			print_ants(a->bonus_color, p[i]->r->ants, p[i]->name);
		}
		else if (p[i]->next && p[i]->next->r->ants > 0)
		{
			p[i]->r->ants = p[i]->next->r->ants;
			p[i]->next->r->ants = 0;
			print_ants(a->bonus_color, p[i]->r->ants, p[i]->name);
			a->end += (p[i]->r->end == 1) ? 1 : 0;
		}
		p[i] = p[i]->next;
	}
	p[i] = tmp[i];
	a->end += (p[i]->r->start == 1 && p[i]->next->r->end == 1) ? 1 : 0;
}

void	handles_path(t_path **p, t_ant *a, int max_path)
{
	int				i;
	static t_path	**tmp = NULL;

	i = -1;
	tmp = (t_path**)malloc(sizeof(t_path) * max_path);
	while (++i < max_path)
		reverse_list(&p[i], a);
	if (max_path > 1)
		sort_multi_path(p, &max_path);
	i = -1;
	while (++i <= max_path)
		tmp[i] = p[i];
	i = -1;
	while (a->end != a->ant)
	{
		while (++i < max_path)
		{
			handles_path_(tmp, &i, p, a);
			if (a->end == a->ant)
				return ;
		}
		i = -1;
		ft_printf("\n");
		p[i] = tmp[i];
	}
}
