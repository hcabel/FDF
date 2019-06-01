/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:11:45 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/01 14:41:45 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_press(int keycode, t_info *info)
{
	if (keycode == UP)
		info->cam->height_z += 0.01 * info->cam->speed;
	if (keycode == DOWN)
		info->cam->height_z -= 0.01 * info->cam->speed;
	if (keycode == ESC)
		finish(info, "End !");
	if (keycode == SPACE)
	{
		info->cam->x = 0;
		info->cam->y = 0;
	}
	if (keycode == TWO && info->cam->color_modifier > 0)
		info->cam->color_modifier--;
	if (keycode == EIGHT && info->cam->color_modifier < 9)
		info->cam->color_modifier++;
	info->cam->speed += 0.25;
	updade_display(info);
	return (0);
}

int		key_release(int keycode, t_info *info)
{
	info->cam->speed = 1;
	if (keycode == ESC)
		finish(info, "End !");
	updade_display(info);
	return (0);
}

int		mouse_press(int button, int x, int y, t_info *info)
{
	(void)x;
	if (y < 0)
		return (0);
	if (button == 1)
		info->mouse->button = 1;
	else if (button == 2)
		info->mouse->button2 = 2;
	return (0);
}

int		mouse_release(int button, int x, int y, t_info *info)
{
	(void)x;
	(void)y;
	if (button == 1)
		info->mouse->button = 0;
	if (button == 2)
		info->mouse->button2 = 0;
	return (0);
}

int		mouse_move(int x, int y, t_info *info)
{
	info->mouse->lastx = info->mouse->x;
	info->mouse->lasty = info->mouse->y;
	info->mouse->x = x;
	info->mouse->y = y;
	if (info->mouse->button == LEFT_CLICK
		&& info->mouse->button2 == RIGHT_CLICK)
	{
		info->cam->offsetx += (x - info->mouse->lastx);
		info->cam->offsety += (y - info->mouse->lasty);
	}
	else if (info->mouse->button == LEFT_CLICK)
	{
		info->cam->x += (double)(info->mouse->lasty - y) / 200;
		info->cam->y -= (double)(info->mouse->lastx - x) / 200;
	}
	else if (info->mouse->button2 == RIGHT_CLICK)
	{
		info->cam->zoom += floor((info->mouse->lasty - y) / 10 + 0.5);
		if (info->cam->zoom < 1)
			info->cam->zoom = 1;
	}
	if (info->mouse->button == 1 || info->mouse->button2 == 2)
		updade_display(info);
	return (0);
}
