/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:06:49 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/21 16:01:11 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static t_vector	*init(t_map *map, t_point **start, t_vector *v, char **stock)
{
	t_point		*tmp;
	t_vector	*v2;
	int			i;

	v2 = cp_vector(*v);
	v2->z = ft_atoi(stock[(int)v2->x]);
	if (ft_strchr(stock[(int)v2->x], ','))
	{
		i = 1;
		while (stock[(int)v2->x][i - 1] != ',')
			i++;
		v2->color = hexa2int(stock[(int)v2->x] + i);
		v2->color_is_define = 1;
	}
	if (v2->z < map->min_z)
		map->min_z = v2->z;
	else if (v2->z > map->max_z)
		map->max_z = v2->z;
	tmp = newlink(cp_vector(*v2));
	if (*start == NULL)
		*start = tmp;
	if (tmp->v->x > 0)
		getref(*start, tmp->v->x - 1, tmp->v->y)->n1 = tmp;
	if (tmp->v->y > 0)
		getref(*start, tmp->v->x, tmp->v->y - 1)->n2 = tmp;
	v2->color_is_define = 0;
	return (v2);
}

t_point			*parsing(t_map *map, int fd, t_info *info)
{
	t_point		*start;
	t_vector	*v;
	char		*line;
	char		**stock;
	int			ret;

	start = NULL;
	v = init_vector(0, 0, 0, info);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		check_file(line, map);
		v->x = 0;
		stock = ft_strsplit(line, ' ');
		while (stock[(int)v->x++])
			v = init(map, &start, v, stock);
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
