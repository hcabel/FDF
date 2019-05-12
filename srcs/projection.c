/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 13:22:21 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/11 23:20:19 by hcabel           ###   ########.fr       */
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
	v.color = p.color;
	return (v);
}

void		isometric_view(t_vector *start, t_vector *end, t_info *info)
{
	t_vector	start2;
	t_vector	end2;

	start2 = *start;
	start2.x -= (double)(info->map->size_x) / 2;
	start2.y -= (double)(info->map->size_y) / 2;
	start2.z *= (double)info->cam->height_z;
	start2.z -= (double)(info->map->min_z + info->map->max_z) / 2;
	start2 = rotate(start2, info->cam);
	start2.x *= info->cam->zoom;
	start2.y *= info->cam->zoom;
	start2.x += info->cam->offsetx;
	start2.y += info->cam->offsety;
	end2 = *end;
	end2.x -= (double)(info->map->size_x) / 2;
	end2.y -= (double)(info->map->size_y) / 2;
	end2.z *= (double)info->cam->height_z;
	end2.z -= (double)(info->map->min_z + info->map->max_z) / 2;
	end2 = rotate(end2, info->cam);
	end2.x *= info->cam->zoom;
	end2.y *= info->cam->zoom;
	end2.x += info->cam->offsetx;
	end2.y += info->cam->offsety;
	line_trace(start2, end2, info);
}

void		parallele_view(t_vector *start, t_vector *end, t_info *info)
{
	t_vector start2;
	t_vector end2;

	start2 = *start;
	end2 = *end;
	start2.x -= (double)(info->map->size_x) / 2;
	start2.x *= info->cam->zoom;
	start2.x += WIN_SIZE_X / 2;
	start2.y -= (double)(info->map->size_y) / 2;
	start2.y *= info->cam->zoom;
	start2.y += WIN_SIZE_Y / 2;
	end2.x -= (double)(info->map->size_x) / 2;
	end2.x *= info->cam->zoom;
	end2.x += WIN_SIZE_X / 2;
	end2.y -= (double)(info->map->size_y) / 2;
	end2.y *= info->cam->zoom;
	end2.y += WIN_SIZE_Y / 2;
	line_trace(start2, end2, info);
}
