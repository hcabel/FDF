/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:30:18 by hcabel            #+#    #+#             */
/*   Updated: 2020/02/21 09:05:37 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

__attribute__((destructor)) void foo(void)
{
	//while (1);
}

int			end(t_info *info)
{
	int	y;

	y = 0;
	while (y < info->map.heigth)
	{
		free(info->map.map[y]);
		y++;
	}
	free(info->map.map);
	free(info->hud.string);
	free(info->hud.ptr);
	free(info->view.string);
	free(info->view.ptr);
	exit(0);
	return (0);
}

static int	out(char *str)
{
	if (*str == '\0')
		ft_putendl("./fdf [maps]");
	else
		ft_putendl(str);
	exit(0);
	return (1);
}

static void	create_images(t_info *info)
{
	info->view.ptr = mlx_new_image(info->mlx_ptr, W_WID - HUD_WID, W_HEIGHT);
	info->view.string = mlx_get_data_addr(info->view.ptr,
		&info->view.bpp, &info->view.s_l, &info->view.endian);
	info->hud.ptr = mlx_new_image(info->mlx_ptr, HUD_WID, W_HEIGHT);
	info->hud.string = mlx_get_data_addr(info->hud.ptr,
		&info->hud.bpp, &info->hud.s_l, &info->hud.endian);
}

static int	setup(t_info *info, char **argv)
{
	info->mlx_ptr = mlx_init();
	info->win_ptr = mlx_new_window(info->mlx_ptr, W_WID, W_HEIGHT, W_NAME);
	create_images(info);
	set_palette(info->obj.palette);
	info->obj.index = 0;
	info->obj.height_z = 1;
	info->obj.offset_x = (W_WID - HUD_WID) / 2;
	info->obj.offset_y = W_HEIGHT / 2;
	info->obj.rot_x = 0;
	info->obj.rot_y = 0;
	info->obj.zoom = 10;
	info->map.heigth = 0;
	info->map.biggest = 0;
	info->map.lower = 0;
	if (parse_map(info, argv[1]))
		return (SETUP_ERROR);
	return (SETUP_GOOD);
}

int			main(int argc, char **argv)
{
	t_info	info;

	if (argc == 1)
		return (out(""));
	if (setup(&info, argv))
		return (out("Setup error"));
	mlx_hook(info.win_ptr, KEY_PRESS, 0, key_press, &info);
	mlx_hook(info.win_ptr, RED_CROSS, 0, end, &info);
	mlx_hook(info.win_ptr, MOUSE_PRESS, 0, mouse_press, &info);
	mlx_hook(info.win_ptr, MOUSE_RELEASE, 0, mouse_release, &info);
	mlx_hook(info.win_ptr, MOUSE_MOVE, 0, mouse_move, &info);
	display_update_hud(info);
	display_update_view(&info);
	mlx_loop(info.mlx_ptr);
	return (0);
}
