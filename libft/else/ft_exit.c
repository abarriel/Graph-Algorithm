/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 01:59:56 by abarriel          #+#    #+#             */
/*   Updated: 2016/11/19 02:00:07 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit(const char *message)
{
	if (message != NULL)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(1);
}
