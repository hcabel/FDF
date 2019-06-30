/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:06:49 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/30 04:03:55 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// LEAK 32 ON BIG MAPS
t_point			*getref(t_point *map, int x, int y)
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

static t_vector	*initi(t_map *map, t_point **start, t_vector *v, char **stock)
{
	t_point		*new;
	t_vector	*v2;
	int			i;

	v2 = cp_vector(*v);
	free(v);
	v2->z = ft_atoi(stock[(int)v2->x]);
	if (ft_strchr(stock[(int)v2->x], ','))
	{
		i = 1;
		while (stock[(int)v2->x][i - 1] != ',')
			i++;
		v2->colour = ft_atoi_base(stock[(int)v2->x] + i, 16);
		v2->colour_is_define = 1;
	}
	if (map->small == NULL || v2->z < map->small->z)
		map->small = v2;
	else if (map->big == NULL || v2->z > map->big->z)
		map->big = v2;
	new = newlink(cp_vector(*v2));
	if (*start == NULL)
		*start = new;
	if (new->v->x > 0)
		getref(*start, new->v->x - 1, new->v->y)->n1 = new;
	if (new->v->y > 0)
		getref(*start, new->v->x, new->v->y - 1)->n2 = new;
	v2->colour_is_define = 0;
	v2->x++;
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
		check_file(line, map, info);
		v->x = 0;
		stock = ft_strsplit(line, ' ');
		while (stock[(int)v->x])
			if ((v = initi(map, &start, v, stock)) == NULL)
				finish(info, "Parsing error !");
		v->y++;
		free(line);
		free_tab(stock);
	}
	if (ret == -1)
		finish(info, "Error file !");
	map->size_x = v->x - 1;
	map->size_y = v->y - 1;
	close(fd);
	free(v);
	return (start);
}
