/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:32:52 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/23 16:55:57 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		if_so_(char conv, char *symb)
{
	char	*tmp;
	char	**tab;
	int		i;

	i = 0;
	tmp = NULL;
	if (symb)
	{
		tmp = symb;
		tab = ft_strsplit(symb, ' ');
	}
	while (tab[i])
		i++;
	if (i == 3)
	{
		if (if_so('-', tab[0]))
			ft_exit("- in the Room's name - Further Explication");
	}
	while (symb && *symb)
	{
		if (conv == *symb)
			return (symb - tmp);
		symb++;
	}
	return (0);
}

t_ant	*init_ant(char *name)
{
	t_ant		*r;
	long		i;

	while (ft_strcmp(name, "##start") &&
			ft_strcmp(name, "##end") && *name == '#')
		get_next_line(0, &name);
	i = ft_atol(name);
	if (i <= 0 || !name || i > INT_MAX)
		ft_exit("Wrong ant's numbers");
	if (!(r = (t_ant*)malloc(sizeof(t_ant))))
		ft_exit("Failed to Malloc");
	r->ant = i;
	r->next = NULL;
	return (r);
}

int		main(void)
{
	parser();
	return (0);
}
