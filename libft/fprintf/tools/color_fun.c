/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 01:22:41 by abarriel          #+#    #+#             */
/*   Updated: 2017/01/10 02:08:42 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_color(int fd, char color_nfun)
{
	if (color_nfun == 1)
		ft_putstr_fd(RED, fd);
	if (color_nfun == 2)
		ft_putstr_fd(GREEN, fd);
	if (color_nfun == 3)
		ft_putstr_fd(BLUE, fd);
	if (color_nfun == 4)
		ft_putstr_fd(PURPLE, fd);
	if (color_nfun == 5)
		ft_putstr_fd(YELLOW, fd);
}

void	color_fun(t_stock *s)
{
	char *tmp;

	if (ft_strncmp(s->str, "{RED}", 5) == 0)
		s->color_nfun = 1;
	if (ft_strncmp(s->str, "{GRE}", 5) == 0)
		s->color_nfun = 2;
	if (ft_strncmp(s->str, "{BLU}", 5) == 0)
		s->color_nfun = 3;
	if (ft_strncmp(s->str, "{PUR}", 5) == 0)
		s->color_nfun = 4;
	if (ft_strncmp(s->str, "{YEL}", 5) == 0)
		s->color_nfun = 5;
	if (s->color_nfun > 0)
	{
		tmp = s->str;
		s->str = ft_strsub(tmp, 5, ft_strlen(s->str) - 5);
	}
}
