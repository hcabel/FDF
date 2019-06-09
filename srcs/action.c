/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:11:45 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/09 16:59:25 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	colour_press(int keycode, t_info *info)
{
	if (keycode == TWO || keycode == TWO_2)
	{
		if (info->cam->colour_mod > 0)
			info->cam->colour_mod--;
		else
			info->cam->colour_mod = 9;
	}
	if (keycode == EIGHT || keycode == EIGHT_2)
	{
		if (info->cam->colour_mod < 9)
			info->cam->colour_mod++;
		else
			info->cam->colour_mod = 0;
	}
	info->cam->speed += 0.25;
}

int			key_press(int keycode, t_info *info)
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
	if (keycode == TWO || keycode == TWO_2 || keycode == EIGHT || keycode == EIGHT_2)
		colour_press(keycode, info);
	info->cam->speed += 0.25;
	update_display(info);
	return (0);
}

int			mouse_press(int button, int x, int y, t_info *info)
{
	if (y < 0)
		return (0);
	if (button == LEFT_CLICK)
		info->mouse->button = LEFT_CLICK;
	else if (button == RIGHT_CLICK)
		info->mouse->button2 = RIGHT_CLICK;
	else if (button == DOWN_WHEEL)
	{
		//info->cam->offsetx += (x / 50);
		//info->cam->offsety += (y / 50);
		info->mouse->button = DOWN_WHEEL;
		info->cam->zoom -= 3;
		info->cam->speed += 0.25;
		if (info->cam->zoom < 1)
			info->cam->zoom = 1;
	}
	else if (button == UP_WHEEL)
	{
		//info->cam->offsetx += (x / 50);
		//info->cam->offsety += (y / 50);
		info->mouse->button = UP_WHEEL;
		info->cam->zoom += 3;
		info->cam->speed += 0.25;
	}
	if (info->mouse->button == 4 || info->mouse->button == 5)
		update_display(info);
	return (0);
}

int			mouse_release(int button, int x, int y, t_info *info)
{
	(void)x;
	(void)y;
	if (button == 1)
		info->mouse->button = 0;
	if (button == 2)
		info->mouse->button2 = 0;
	if (button == 4)
		info->mouse->button = 0;
	if (button == 5)
		info->mouse->button = 0;
	return (0);
}

int			mouse_move(int x, int y, t_info *info)
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
		update_display(info);
	return (0);
}


