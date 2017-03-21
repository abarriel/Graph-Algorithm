/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:32:52 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/21 23:56:45 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		if_so_(char conv, char *symb)
{
	char	*tmp;
	char	**tab;
	int		i;

	i = 0;
	tab = NULL;
	tmp = NULL;
	if (symb)
	{
		tmp = symb;
		tab = ft_strsplit(symb, ' ');
	}
	while (tab[i])
		i++;
	free_split(tab);
	while (symb && *symb)
	{
		if (conv == *symb)
			return (symb - tmp);
		symb++;
	}
	return (0);
}

void	init_ant_(t_ant *r, int bc, int bp)
{
	r->start = r->ant;
	r->end = 0;
	r->dant = 0;
	r->bonus_color = bc;
	r->bonus_path = bp;
}

t_ant	*init_ant(char *name, int bp, int bc)
{
	t_ant		*r;
	long		i;
	static int	a = -1;

	while (ft_strcmp(name, "##start") &&
			ft_strcmp(name, "##end") && *name == '#')
	{
		ft_strdel(&name);
		get_next_line(0, &name);
	}
	while (name[++a])
	{
		if (name[a] != '\0' && (name[a] < 48 || name[a] > 57))
			ft_exit("Wrong ant's numbers");
	}
	i = ft_atol(name);
	if (i <= 0 || !name || i > INT_MAX)
		ft_exit("Wrong ant's numbers");
	if (!(r = (t_ant*)malloc(sizeof(t_ant))))
		ft_exit("Failed to Malloc");
	ft_strdel(&name);
	r->ant = i;
	init_ant_(r, bc, bp);
	return (r);
}

void	bonus_lemin(int *bc, int *bp, char **ac)
{
	int	i;

	i = 1;
	while (ac[i])
	{
		if (ft_strcmp("-c", ac[i]) == 0)
			(*bp)++;
		else if (ft_strcmp("-p", ac[i]) == 0)
			(*bc)++;
		else
			ft_exit("error args");
		i++;
	}
}

int		main(int ac, char **av)
{
	int		bc;
	char	*line;
	int		bp;

	bc = 0;
	bp = 0;
	line = NULL;
	if (ac > 1)
		bonus_lemin(&bc, &bp, av);
	parser(bc, bp, line);
	return (0);
}
