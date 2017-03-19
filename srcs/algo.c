#include "lemin.h"

void	algo_lem__(t_room **r1, t_tube **tmp1, t_room *begin, t_room *debut)
{
	t_room	*r;
	t_tube	*tmp;

	r = *r1;
	tmp = *tmp1;
	r->tube = r->tube->next;
	if (!r->tube)
	{
		r->poids = 2;
		r->tube = tmp;
		verif(begin);
		r = debut;
	}
	*r1 = r;
	*tmp1 = tmp;
}

int		algo_lem_(t_room **r1, t_tube **tmp1, t_room *begin, t_room *debut)
{
	t_room	*r;
	t_tube	*tmp;

	r = *r1;
	tmp = *tmp1;
	if (r->tube == NULL)
		return (0);
	if (r->tube->room->poids == 0)
	{
		r->tube->room->poids = 1;
		r = r->tube->room;
	}
	else
		algo_lem__(&r, &tmp, begin, debut);
	*r1 = r;
	*tmp1 = tmp;
	return (1);
}

int		algo_lem___(t_tube **tmp, t_room **r)
{
	while ((*tmp))
	{
		(*tmp)->room->end = ((*tmp)->room->by == 4) ? 2 : (*tmp)->room->end;
		if ((*tmp)->room->end == 1)
		{
			(*r) = (*tmp)->room;
			(*r)->poids = 1;
			return (0);
		}
		(*tmp) = (*tmp)->next;
	}
	return (1);
}

void	algo_lem(t_room *r)
{
	t_tube	*tmp;
	t_room	*begin;
	t_room	*debut;

	begin = r;
	while (r->start != 1 && r)
		r = r->next;
	r->poids = 2;
	debut = r;
	if (!check_stop(r->tube))
		return ;
	while (r->end != 1)
	{
		if (!verif_no(begin))
			ft_exit("Invalid Path");
		tmp = r->tube;
		if (!algo_lem___(&tmp, &r))
			return ;
		tmp = r->tube;
		if (!algo_lem_(&r, &tmp, begin, debut))
			return ;
	}
	return ;
}

void	handles_algo(t_room *r, t_ant *a)
{
	t_path	**path;
	int		i;
	int		b;
	int		j;

	i = 0;
	b = -1;
	if (!(j = multi_path(r, a)))
		ft_exit("Invalid Path");
	path = (t_path **)malloc(sizeof(t_path *) * j);
	while (i == 0 && ++b < j)
	{
		algo_lem(r);
		path[b] = save_path(r, &i);
		if (!path[b])
		{
			j = b;
			break ;
		}
		else if (a->bonus_path == 1)
			print_path(path[b]);
	}
	if (!(path[0]))
		ft_exit("Invalid Path");
	handles_path(path, a, j);
}
