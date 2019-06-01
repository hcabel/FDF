/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 13:22:21 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/01 14:08:08 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	rotate(t_vector p, t_cam *r)
{
	t_vector	v;
	double		x;
	double		y;
	double		z;

	x = p.x;
	z = p.z;
	v.x = cos(r->y) * x + sin(r->y) * z;
	v.z = -sin(r->y) * x + cos(r->y) * z;
	y = p.y;
	z = v.z;
	v.y = cos(r->x) * y - sin(r->x) * z;
	v.z = sin(r->x) * y + cos(r->x) * z;
	return (v);
}

static void	setup(t_vector *v, int color, int define, t_info *info)
{
	int index;
	int z;

	z = v->z;
	index = info->cam->color_modifier;
	v->x -= (double)(info->map->size_x) / 2;
	v->y -= (double)(info->map->size_y) / 2;
	v->z *= (double)info->cam->height_z;
	v->z -= (double)(info->map->smallest->z + info->map->biggest->z) / 2;
	*v = rotate(*v, info->cam);
	v->x *= info->cam->zoom;
	v->y *= info->cam->zoom;
	v->x += info->cam->offsetx;
	v->y += info->cam->offsety;
	v->color_is_define = define;
	if (v->color_is_define == 1)
		v->color = color;
	else
		v->color = set_color(info->map->smallest->color, info->map->biggest->color
			, get_percent(info->map->smallest->z, info->map->biggest->z, z));
}

void		isometric_view(t_vector *start, t_vector *end, t_info *info)
{
	t_vector	start2;
	t_vector	end2;

	start2 = *start;
	end2 = *end;
	setup(&start2, start->color, start->color_is_define, info);
	setup(&end2, end->color, end->color_is_define, info);
	line_trace(start2, end2, info);
}
