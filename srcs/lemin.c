/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:32:52 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/11 07:50:51 by abarriel         ###   ########.fr       */
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
	while (symb && *symb)
	{
		if (conv == *symb)
			return (symb - tmp);
		symb++;
	}
	return (0);
}

t_ant	*init_ant(char *name, int bp, int bc)
{
	t_ant	*r;
	long	i;

	while (ft_strcmp(name, "##start") &&
			ft_strcmp(name, "##end") && *name == '#')
		get_next_line(0, &name);
	i = ft_atol(name);
	ft_printf("%s\n");
	if (i <= 0 || !name || i > INT_MAX)
		ft_exit("Wrong ant's numbers");
	if (!(r = (t_ant*)malloc(sizeof(t_ant))))
		ft_exit("Failed to Malloc");
	r->ant = i;
	r->start = r->ant;
	r->end = 0;
	r->dant = 0;
	r->bonus_color = bc;
	r->bonus_path = bp;
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
		i++;
	}
}

int		main(int ac, char **av)
{
	int	bc;
	int	bp;

	bc = 0;
	bp = 0;
	if (ac > 1)
		bonus_lemin(&bc, &bp, av);
	parser(bc, bp);
	return (0);
}
