/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:51:30 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/11 22:44:06 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_hud_string(t_info *info)
{
	mlx_string_put(info->mlx_ptr, info->win_ptr, 50, 25, 0xFFFFFF,
		"Mouse :");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 75, 50, 0xFFFFFF,
		"right button");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 100, 75, 0xFFFFFF,
		"zoom");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 75, 100, 0xFFFFFF,
		"left button");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 100, 125, 0xFFFFFF,
		"rotate");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 75, 150, 0xFFFFFF,
		"left button and right button");
	mlx_string_put(info->mlx_ptr, info->win_ptr, 100, 175, 0xFFFFFF,
		"drag and drop");
}

void	add_hud(char **string)
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
			if ((x > HUD_SIZE - HUD_BORDER_SIZE && x < HUD_SIZE)
				|| (y < HUD_BORDER_SIZE || y > WIN_SIZE_Y - HUD_BORDER_SIZE))
				*(int *)(*(string) + ((x + y * WIN_SIZE_X) * 4)) = 0xAAAAAA;
			else if (y < WIN_SIZE_Y / 2)
			{
				percent = get_percent((int)0, (int)WIN_SIZE_Y / 2, (int)y);
				*(int *)(*(string) + ((x + y * WIN_SIZE_X) * 4)) =
					set_color(0x222222, 0x303030, percent);
			}
			else
			{
				percent = get_percent((int)WIN_SIZE_Y / 2, (int)WIN_SIZE_Y, (int)y);
				*(int *)(*(string) + ((x + y * WIN_SIZE_X) * 4)) =
					set_color(0x303030, 0x222222, percent);
			}
			x++;
		}
		y++;
	}
}
