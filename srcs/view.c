/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:09:03 by sylewis           #+#    #+#             */
/*   Updated: 2019/09/21 16:23:14 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <fcntl.h>

static t_vector	rotate(t_vector p, t_info info)
{
	t_vector	v;
	double		x;
	double		y;
	double		z;

	x = p.x;
	z = p.z;
	v.x = cos(info.obj.rot_y) * x + sin(info.obj.rot_y) * z;
	v.z = -sin(info.obj.rot_y) * x + cos(info.obj.rot_y) * z;
	y = p.y;
	z = v.z;
	v.y = cos(info.obj.rot_x) * y - sin(info.obj.rot_x) * z;
	v.z = sin(info.obj.rot_x) * y + cos(info.obj.rot_x) * z;
	return (v);
}

static t_vector	setup_position(int x, int y, int z, t_info *info)
{
	t_vector	v;
	double		percent;

	v.x = (x - (double)info->map.width / 2) * info->obj.zoom;
	v.y = (y - (double)info->map.heigth / 2) * info->obj.zoom;
	v.z = z * info->obj.height_z * info->obj.zoom / 5;
	v = rotate(v, *info);
	v.x += info->obj.offset_x;
	v.y += info->obj.offset_y;
	z = z * info->obj.height_z;
	if (z >= info->map.lower + info->obj.colormidline && z <= info->map.biggest
		+ info->obj.colormidline)
		percent = get_percent(info->map.lower + info->obj.colormidline
			, info->map.biggest
		+ info->obj.colormidline, z);
	else
	{
		if (z < info->map.lower + info->obj.colormidline)
			percent = 0;
		else
			percent = 1;
	}
	v.colour = set_colour(info->obj.palette[info->obj.index][0],
		info->obj.palette[info->obj.index][1], percent);
	return (v);
}

static void		create_link(int x, int y, t_info *info)
{
	t_vector	start;
	t_vector	end;

	start = setup_position(x, y, info->map.map[y][x], info);
	if (x + 1 < info->map.width)
	{
		end = setup_position(x + 1, y, info->map.map[y][x + 1], info);
		line_trace(start, end, info);
	}
	if (y + 1 < info->map.heigth)
	{
		end = setup_position(x, y + 1, info->map.map[y + 1][x], info);
		line_trace(start, end, info);
	}
}

static void		display(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < info->map.heigth)
	{
		x = 0;
		while (x < info->map.width)
		{
			create_link(x, y, info);
			x++;
		}
		y++;
	}
}

void			display_update_view(t_info *info)
{
	ft_bzero(info->view.string, ((W_WID - HUD_WID) * W_HEIGHT) * 4);
	display(info);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->view.ptr,
		HUD_WID - 1, 0);
}
