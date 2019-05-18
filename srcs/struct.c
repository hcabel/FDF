/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:28:50 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/18 13:24:13 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	*init_vector(double x, double y, double z)
{
	t_vector *v;

	if (!(v = (t_vector*)malloc(sizeof(t_vector))))
		return (0);
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

t_vector	*cp_vector(t_vector v2)
{
	t_vector *v;

	if (!(v = (t_vector*)malloc(sizeof(t_vector))))
		return (0);
	v->x = v2.x;
	v->y = v2.y;
	v->z = v2.z;
	return (v);
}

t_map		*init_map(char *argv)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (0);
	map->size_x = 0;
	map->size_y = 0;
	map->nb_nb = -1;
	map->min_z = 0;
	map->max_z = 0;
	map->start = parsing(map, open(argv, O_RDONLY));
	return (map);
}

t_point		*newlink(t_vector *v)
{
	t_point	*new;

	if (!(new = (t_point*)malloc(sizeof(t_point))))
		finish("Allocation failed");
	new->v = v;
	new->v->color = 0x540099;
	new->n1 = NULL;
	new->n2 = NULL;
	new->n1_isprint = 0;
	new->n2_isprint = 0;
	return (new);
}
