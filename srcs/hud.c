/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:51:30 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/01 14:44:47 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_hud_string(t_info *info)
{
	mlx_string_put(info->mlx_ptr, info->win_ptr, 50, 25, 0xF40099, "Mouse :");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 75, 50, 0x1FFFFF,
		"right button");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 100, 75, 0xFFFFFF, "zoom");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 75, 100, 0x1FFFFF,
		"left button");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 100, 125, 0xFFFFFF, "rotate");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 75, 150, 0x1FFFFF,
		"left button and right button");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 100, 175, 0xFFFFFF,
		"drag and drop");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 50, 225, 0xF40099,
		"Keyboard :");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 75, 250, 0x1FFFFF,
		"Up arrow and Down arrow");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 100, 275, 0xFFFFFF,
		"Change height");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 75, 300, 0x1FFFFF,
		"Numpad 8 and Numpad 2");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 100, 325, 0xFFFFFF,
		"Change color palette");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 75, 350, 0x1FFFFF,
		"Space bar");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 100, 375, 0xFFFFFF,
		"Top view");
}

void		add_hud(char **string, t_info *info)
{
	double	percent;
	int		x;
	int		y;

	y = 0;
	while (y < WIN_SIZE_Y)
	{
		x = 0;
		while (x < HUD_SIZE)
		{
			if ((x > (HUD_SIZE / 10) && x < HUD_SIZE - HUD_BORDER_SIZE - (HUD_SIZE / 10))
				&& (y > (WIN_SIZE_Y / 20) * 18 && y <(WIN_SIZE_Y / 20) * 19))
			{
				percent = get_percent((HUD_SIZE / 10), HUD_SIZE - HUD_BORDER_SIZE, (int)x);
				*(int *)(*(string) + ((x + y * WIN_SIZE_X) * 4)) =
					set_color(info->cam->color_palette[info->cam->color_modifier][0],
						info->cam->color_palette[info->cam->color_modifier][1], percent);
			}
			else if ((x > HUD_SIZE - HUD_BORDER_SIZE && x < HUD_SIZE)
				|| (y < HUD_BORDER_SIZE || y > WIN_SIZE_Y - HUD_BORDER_SIZE))
				*(int *)(*(string) + ((x + y * WIN_SIZE_X) * 4)) = 0xAAAAAA;
			else
			{
				percent = get_percent(WIN_SIZE_Y, 0, (int)y);
				*(int *)(*(string) + ((x + y * WIN_SIZE_X) * 4)) =
					set_color(0x222222, 0x303030, percent);
			}
			x++;
		}
		y++;
	}
}
