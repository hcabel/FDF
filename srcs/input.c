/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 00:28:49 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/21 16:26:56 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	colour_press(int keycode, t_info *info)
{
	if (keycode == TWO || keycode == NUM_TWO)
	{
		if (info->obj.index > 0)
			info->obj.index--;
		else
			info->obj.index = 9;
	}
	else if (keycode == EIGHT || keycode == NUM_EIGHT)
	{
		if (info->obj.index < 9)
			info->obj.index++;
		else
			info->obj.index = 0;
	}
}

int			key_press(int keycode, t_info *info)
{
	if (keycode == UP)
		info->obj.height_z += 0.05;
	if (keycode == DOWN)
		info->obj.height_z -= 0.05;
	if (keycode == W)
		info->obj.colormidline += 0.5 + info->map.biggest / 20;
	if (keycode == S)
		info->obj.colormidline -= 0.5 + info->map.biggest / 20;
	if (keycode == SPACE)
	{
		info->obj.rot_x = 0;
		info->obj.rot_y = 0;
	}
	else if (keycode == ESC)
		end(info);
	if (keycode == TWO || keycode == EIGHT || keycode == NUM_TWO ||
		keycode == NUM_EIGHT || keycode == SPACE || keycode == UP
		|| keycode == DOWN || keycode == W || keycode == S)
	{
		colour_press(keycode, info);
		display_update_hud(*info);
		display_update_view(info);
	}
	return (0);
}

int			mouse_press(int button, int x, int y, t_info *info)
{
	(void)x;
	(void)y;
	info->mouse.button = button;
	if (info->mouse.button == UP_WHEEL)
		info->obj.zoom += 0.5;
	else if (info->mouse.button == DOWN_WHEEL)
		info->obj.zoom -= 0.5;
	display_update_view(info);
	return (0);
}

int			mouse_release(int button, int x, int y, t_info *info)
{
	(void)button;
	(void)x;
	(void)y;
	info->mouse.button = 0;
	return (0);
}

int			mouse_move(int x, int y, t_info *info)
{
	info->mouse.last_x = info->mouse.current_x;
	info->mouse.last_y = info->mouse.current_y;
	info->mouse.current_x = x;
	info->mouse.current_y = y;
	if (info->mouse.button == LEFT_CLICK)
	{
		info->obj.rot_x += (double)(info->mouse.last_y - y) / 200;
		info->obj.rot_y -= (double)(info->mouse.last_x - x) / 200;
	}
	else if (info->mouse.button == RIGHT_CLICK)
	{
		info->obj.offset_x += x - info->mouse.last_x;
		info->obj.offset_y += y - info->mouse.last_y;
	}
	display_update_view(info);
	return (0);
}
