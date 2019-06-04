/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:13:38 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/03 14:07:47 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_cam	*init_cam(t_info *info, int colour)
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
	cam->colour_modifier = 0;
	cam->basecolour = colour;
	cam->colour_palette = colour_palette(info); 
	return (cam);
}

static t_mouse	*init_mouse(t_info *info)
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

t_info			*init(int argc, char **argv)
{
	t_info	*info;
	int		i;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		finish(info, "Allocation failed");
	info->mlx_ptr = mlx_init();
	info->win_ptr = mlx_new_window(info->mlx_ptr, WIN_SIZE_X,
		WIN_SIZE_Y, WIN_NAME);
	info->img = init_image(info);
	info->cam = init_cam(info, (argc == 3 ? hexa2int(argv[2], info) : 0xFFF));
	info->mouse = init_mouse(info);
	info->map = init_map(argv[1], info);
	i = 0;
	if (info->map->nb_nb <= 1)
		finish (info, "Error map ! {- Please add more points -}");
	while (info->map->size_x * (i + 50) < WIN_SIZE_X - HUD_SIZE
		&& info->map->size_y * (i + 50) < WIN_SIZE_Y)
		i++;
	info->cam->zoom = i;
	return (info);
}
