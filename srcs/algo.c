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

void  verif(t_room *r)
{
    while(r)
    {

        if (r->poids == 1)
            r->poids = 0;
        r = r->next;
    }
} 

void algo_lem__(t_room **r1, t_tube **tmp1, t_room *begin)
{
    t_room *r;
    t_tube *tmp;
    
    r = *r1;
    tmp = *tmp1;
    
    r->tube = r->tube->next;
    if (!r->tube)
    {
        r->poids = 2;
        verif(begin);
        r = begin;
    }
    *r1 = r;
    *tmp1 = tmp;
}

int    algo_lem_(t_room **r1, t_tube **tmp1, t_room *begin)
{
    t_room *r;
    t_tube *tmp;
    
    r = *r1;
    tmp = *tmp1;
    if (r->tube == NULL)
        return 0;
    if (r->tube->room->poids == 0)
    {
        r->tube->room->poids = 1;
        r = r->tube->room;
    }
    else 
      algo_lem__(&r,&tmp,begin);
    *r1 = r;
    *tmp1 = tmp;
    return 1;
}

void    adolf(t_room *r)
{
    while(r->tube)
    {
        if (r->tube->room->poids == 1 || r->tube->room->poids == 0)
            return ;
        else
            ft_exit("OK");
        r->tube = r->tube->next;
    }
}
void	algo_lem(t_room *r)
{
    t_tube *tmp;
    t_room *verif;
    t_room *begin;

    begin = r;
    while (r->start != 1 && r)
        r = r->next;
    verif = r;
    r->poids = 1;
    while (r->end != 1)
    {
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
        if(!algo_lem_(&r,&tmp, begin))
            return ;
    }
    return ;
}

void    handles_algo(t_room *r, t_ant *a)
{
    t_path  **path;
    int     i;
    int     j;

    i = 0;
    j = 0;
    path = (t_path **)malloc(sizeof(t_path *) * 50);
    while(i == 0 && j < 50)
    {
        algo_lem(r);
        path[j] = save_path(r, &i);
        print_path(path[j]);
        j++;
    }
}