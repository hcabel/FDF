/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:06:49 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/12 11:42:19 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
static int		check_file(char *ln, t_map *map)
{
	int		i;
	int		nb_nb;

	i = -1;
	nb_nb = 0;
	while (ln[++i])
	{
		if (!ft_isdigit(ln[i]) && ln[i] != ' ')
			return(1);
		else if (ft_isdigit(ln[i])
			&& (!(ft_isprint(ln[i - 1]) || ln[i - 1] == ' ')))
			nb_nb++;
	}
	printf("test %d\n", nb_nb);
	if (map->nb_nb == 0 && nb_nb > 1)
		map->nb_nb = nb_nb;
	if (ft_strlen(ln) <= 2 || map->nb_nb != nb_nb)
		return (1);
	map->nb_nb = nb_nb;
	return (0);
}*/

static t_point	*getref(t_point *map, int x, int y)
{
	t_point *ref;

	ref = map;
	while (x > 0)
	{
		ref = ref->n1;
		x--;
	}
	while (y > 0)
	{
		ref = ref->n2;
		y--;
	}
	return (ref);
}

static void		addtomap(t_point *map, t_point *new)
{
	if (new->v->x - 1 >= 0)
		getref(map, new->v->x - 1, new->v->y)->n1 = new;
	if (new->v->y - 1 >= 0)
		getref(map, new->v->x, new->v->y - 1)->n2 = new;
}

t_point			*parsing(t_map *map, int fd)
{
	t_point		*start;
	t_vector	*v;
	char		*line;
	char		**stock;
	int			ret;

	start = NULL;
	v = init_vector(0, 0, 0);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		v->x = 0;
		stock = ft_strsplit(line, ' ');
		while (stock[(int)v->x])
		{
			v->z = ft_atoi(stock[(int)v->x]);
			if (v->z < map->min_z)
				map->min_z = v->z;
			else if (v->z > map->max_z)
				map->max_z = v->z;
			if (start == NULL)
				start = newlink(cp_vector(*v));
			addtomap(start, newlink(cp_vector(*v)));
			v->x++;
		}
		v->y++;
	}
	if (ret == -1)
		finish("Error file !");
	map->size_x = v->x - 1;
	map->size_y = v->y - 1;
	return (start);
}
