/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:52:46 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/01 02:37:15 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void algo_lem__(t_room **r1, t_tube **tmp1)
{
    t_room *r;
    t_tube *tmp;
    
    r = *r1;
    tmp = *tmp1;
    
    r->tube = r->tube->next;
    if (!r->tube)
    {
        r->poids = 2;
        r->tube = tmp;
        while (r->tube->prev)
            r->tube = r->tube->prev;
        while (r->tube->room->poids != 1 && r->tube->next)
            r->tube = r->tube->next;
        if (r->tube->room->poids != 1 && r->tube->next == NULL)
            ft_exit("Invalid Path");
        r = r->tube->room;
    }
    *r1 = r;
    *tmp1 = tmp;
}
void algo_lem_(t_room **r1, t_tube **tmp1)
{
    t_room *r;
    t_tube *tmp;
    
    r = *r1;
    tmp = *tmp1;
    if (r->tube == NULL)
        ft_exit("Invalid Path\n");
    if (r->tube->room->poids == 0)
    {
        r->tube->room->poids = 1;
        r = r->tube->room;
    }
    else
        algo_lem__(&r,&tmp);
    *r1 = r;
    *tmp1 = tmp;
}

void	algo_lem(t_room *r)
{
    t_tube *tmp;
    
    while (r->start != 1 && r)
        r = r->next;
    r->poids = 1;
    while (r->end != 1)
    {
        if (r->start == 1 && r->poids == 2)
            exit(0);
        tmp = r->tube;
        while (tmp)
        {
            if (tmp->room->end == 1)
            {
                r = tmp->room;
                r->poids = 1;
                return ;
            }
            tmp = tmp->next;
        }
        tmp = r->tube;
        algo_lem_(&r,&tmp);
    }
    return ;
}

void change_r(t_room *r)
{
    while(r)
    {
        r->by = 0;
        while(r->tube->next)
        {
            if(r->tube->room->poids != 0)
                r->tube->room->poids = 0;
            r->tube = r->tube->next;
        }
        while(r->tube->prev)
            r->tube = r->tube->prev;
        if (r->start == 1)
        {
            r->start = 0;
            r->end = 1;
            r->x = 45;
        }
        if (r->end == 1 && r->x != 45)
        {
            r->end = 0;
            r->start = 1;
        }
        r = r->next;
    }

}

void handles_algo(t_room *r, t_ant *a)
{
    poids(r);
	print_room(r);
    // algo_lem(r);
    // change_r(r);
    // print_room(r);
    // print_room_r(r);
    // algo_lem(r);
    // print_room_rj(r);
    // change_r(r);
    // algo_lem(r);
    // print_room(r);
    // print_room_rj(r);
      // algo_lem(r);
    // print_room_rj4(r);

}