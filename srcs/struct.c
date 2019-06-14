/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:28:50 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/11 15:01:41 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	*init_vector(double x, double y, double z, t_info *info)
{
	t_vector *v;

	if (!(v = (t_vector*)ft_memalloc(sizeof(t_vector))))
		finish(info, "Allocation failed");
	v->x = x;
	v->y = y;
	v->z = z;
	v->colour_is_define = 0;
	v->colour = 0;
	return (v);
}

t_vector	*cp_vector(t_vector v2, t_info *info)
{
	t_vector *v;

	if (!(v = (t_vector*)ft_memalloc(sizeof(t_vector))))
		finish(info, "Allocation failed");
	v->x = v2.x;
	v->y = v2.y;
	v->z = v2.z;
	v->colour_is_define = v2.colour_is_define;
	v->colour = v2.colour - (v2.z * 50);
	return (v);
}

t_map		*init_map(char *argv, t_info *info)
{
	t_map	*map;

	if (!(map = (t_map*)ft_memalloc(sizeof(t_map))))
		finish(info, "Allocation failed");
	map->size_x = 0;
	map->size_y = 0;
	map->nb_nb = -1;
	map->big = NULL;
	map->small = NULL;
	map->start = parsing(map, open(argv, O_RDONLY), info);
	return (map);
}

t_point		*newlink(t_vector *v, t_info *info)
{
	t_point	*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
		finish(info, "Allocation failed");
	new->v = v;
	new->n1 = NULL;
	new->n2 = NULL;
	new->n1_isprint = 0;
	new->n2_isprint = 0;
	return (new);
}
