/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 05:02:47 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/11 08:03:44 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_path(t_path *path)
{
	if (!path)
		return ;
	while (path)
	{
		ft_printf("%s", path->name);
		if (path->next)
			ft_printf("->");
		path = path->next;
	}
	ft_printf("\n\n");
}

void	print_ants(int bc, int ants, char *name)
{
	int	i;

	i = 1;
	if (bc == 0)
	{
		ft_printf("L%d-%s ", ants, name);
		return ;
	}
	i = ants;
	if (ants > 256)
		i = ants - 256;
	ft_putstr("\e[38;5;");
	ft_putnbr(i);
	ft_putstr("m");
	ft_printf("L%d-%s ", ants, name);
	ft_putstr(RESET);
}
