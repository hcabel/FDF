/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:06:49 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/18 11:34:55 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		count_point(char *ln)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (ln[i])
	{
		if (ft_isdigit(ln[i]))
		{
			result++;
			while (ft_isdigit(ln[i]))
				i++;
		}
		i++;
	}
	return (result);
}

static int		check_file(char *ln, t_map *map)
{
	int		nb_point;

	nb_point = count_point(ln);
	printf("%d", nb_point);
	if (nb_point != map->nb_nb && map->nb_nb != -1)
		finish("");
	return (0);
}

static t_point	*getref(t_point *map, int x, int y)
{
	t_point *ref;

	ref = map;
	while (x-- > 0)
		if (ref->n1)
			ref = ref->n1;
	while (y-- > 0)
		if (ref->n2)
			ref = ref->n2;
	return (ref);
}

static void		addtomap(t_point *map, t_point *new)
{
	if (new->v->x > 0)
		getref(map, new->v->x - 1, new->v->y)->n1 = new;
	if (new->v->y > 0)
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
		//check_file(line, map);
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
	close(fd);
	free(v);
	return (start);
}
