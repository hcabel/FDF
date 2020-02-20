/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 12:06:17 by hcabel            #+#    #+#             */
/*   Updated: 2020/01/04 22:45:59 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	add_hud_string2(t_info info)
{
	mlx_string_put(info.mlx_ptr, info.win_ptr, 100, 375, 0xFFFFFF,
		"Top view");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 75, 400, 0x1FFFFF,
		"Color offset");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 100, 425, 0xFFFFFF,
		"W and S");
}

static void	add_hud_string(t_info info)
{
	mlx_string_put(info.mlx_ptr, info.win_ptr, 50, 25, 0xF40099, "Mouse :");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 75, 50, 0x1FFFFF,
		"wheel");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 100, 75, 0xFFFFFF, "zoom");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 75, 100, 0x1FFFFF,
		"left button");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 100, 125, 0xFFFFFF, "rotate");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 75, 150, 0x1FFFFF,
		"right button");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 100, 175, 0xFFFFFF,
		"drag and drop");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 50, 225, 0xF40099,
		"Keyboard :");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 75, 250, 0x1FFFFF,
		"Up arrow and Down arrow");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 100, 275, 0xFFFFFF,
		"Change height");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 75, 300, 0x1FFFFF, "8 and 2");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 100, 325, 0xFFFFFF,
		"Change colour palette");
	mlx_string_put(info.mlx_ptr, info.win_ptr, 75, 350, 0x1FFFFF,
		"Space bar");
	add_hud_string2(info);
}

static void	action(char **string, int x, int y, t_info info)
{
	double	percent;

	if ((x > (HUD_WID / 10) && x < HUD_WID - 4 - (HUD_WID / 10))
		&& (y > (W_HEIGHT / 20) * 18 && y < (W_HEIGHT / 20) * 19))
	{
		percent = get_percent((HUD_WID / 10), HUD_WID - 4, (int)x);
		*(int *)(*(string) + ((x + y * HUD_WID) * 4)) =
			set_colour(info.obj.palette[info.obj.index][0],
			info.obj.palette[info.obj.index][1], percent);
	}
	else if ((x > HUD_WID - 4 || x < 4) || (y < 4 || y > W_HEIGHT - 4))
		*(int *)(*(string) + ((x + y * HUD_WID) * 4)) = 0xAAAAAA;
	else
	{
		percent = get_percent(W_HEIGHT, 0, (int)y);
		*(int *)(*(string) + ((x + y * HUD_WID) * 4)) =
			set_colour(0x222222, 0x303030, percent);
	}
}

static void	add_hud_background(char **string, t_info info)
{
	int		x;
	int		y;

	y = 0;
	while (y < W_HEIGHT - 1)
	{
		x = 0;
		while (x < HUD_WID - 1)
		{
			action(string, x, y, info);
			x++;
		}
		y++;
	}
}

void		display_update_hud(t_info info)
{
	ft_bzero(info.hud.string, HUD_WID * W_HEIGHT * 4);
	add_hud_background(&(info.hud.string), info);
	mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.hud.ptr, 0, 0);
	add_hud_string(info);
}
