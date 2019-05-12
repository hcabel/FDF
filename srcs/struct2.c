/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:13:38 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/11 23:17:53 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_cam	*init_cam(void)
{
	t_cam	*cam;

	if (!(cam = (t_cam*)malloc(sizeof(t_cam))))
		finish("Allocation failed");
	cam->projection = isometric_view;
	cam->speed = 1;
	cam->height_z = 1;
	cam->offsetx = WIN_SIZE_X / 2 + (HUD_SIZE / 2);
	cam->offsety = WIN_SIZE_Y / 2;
	cam->x = 0.1;
	cam->y = 0.1;
	return (cam);
}

t_mouse	*init_mouse(void)
{
	t_mouse	*mouse;

	if (!(mouse = (t_mouse*)malloc(sizeof(t_mouse))))
		finish("Allocation failed");
	mouse->x = 0;
	mouse->y = 0;
	mouse->lastx = 0;
	mouse->lasty = 0;
	return (mouse);
}

t_info	*init_info(char *argv)
{
	t_info	*info;
	int i;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		finish("Allocation failed");
	info->mlx_ptr = mlx_init();
	info->win_ptr = mlx_new_window(info->mlx_ptr, WIN_SIZE_X,
		WIN_SIZE_Y, WIN_NAME);
	info->img = init_image(info);
	info->cam = init_cam();
	info->mouse = init_mouse();
	info->map = init_map(argv);
	i = 0;
	while (info->map->size_x * (i + 2) < WIN_SIZE_X - HUD_SIZE
		&& info->map->size_y * (i + 2) < WIN_SIZE_Y)
		i++;
	info->cam->zoom = i;
	return (info);
}
