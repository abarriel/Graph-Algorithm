/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:32:52 by abarriel          #+#    #+#             */
/*   Updated: 2017/02/19 11:32:54 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ant	*init_ant(char *name)
{
	t_ant	*r;
	int		i;

	if (!(i = ft_atoi(name)) || !name)
		ft_exit("Setting up failed bc missing value or Empty files");
	if (!(r = (t_ant*)malloc(sizeof(t_ant))))
		ft_exit("Failed to Malloc");
 	r->ant = i;
	r->next = NULL;
	return(r);

}


int		main(void)
{
	parser();
	return (0);
}
