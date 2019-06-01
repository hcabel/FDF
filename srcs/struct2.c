/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:13:38 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/01 14:36:06 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_cam	*init_cam(t_info *info)
{
	t_cam	*cam;

	if (!(cam = (t_cam*)malloc(sizeof(t_cam))))
		finish(info, "Allocation failed");
	cam->projection = isometric_view;
	cam->speed = 1;
	cam->height_z = 1;
	cam->offsetx = WIN_SIZE_X / 2 + (HUD_SIZE / 2);
	cam->offsety = WIN_SIZE_Y / 2;
	cam->x = -0.5;
	cam->y = 0.5;
	cam->colour_modifier = 1;
	return (cam);
}

t_mouse	*init_mouse(t_info *info)
{
	t_mouse	*mouse;

	if (!(mouse = (t_mouse*)malloc(sizeof(t_mouse))))
		finish(info, "Allocation failed");
	mouse->x = 0;
	mouse->y = 0;
	mouse->lastx = 0;
	mouse->lasty = 0;
	return (mouse);
}

t_info	*init_info(int argc, char **argv)
{
	t_info	*info;
	int		i;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		finish(info, "Allocation failed");
	info->mlx_ptr = mlx_init();
	info->win_ptr = mlx_new_window(info->mlx_ptr, WIN_SIZE_X,
		WIN_SIZE_Y, WIN_NAME);
	info->img = init_image(info);
	info->cam = init_cam(info);
	info->mouse = init_mouse(info);
	info->basecolour = (argc == 3 ? hexa2int(argv[2], info) : 0xFFFFFF);
	info->map = init_map(argv[1], info);
	i = 0;
	if (info->map->nb_nb <= 1)
		finish (info, "Error map ! {- Please add mor point -}");
	while (info->map->size_x * (i + 50) < WIN_SIZE_X - HUD_SIZE
		&& info->map->size_y * (i + 50) < WIN_SIZE_Y)
		i++;
	info->cam->zoom = i;
	return (info);
}
