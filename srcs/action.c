/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:11:45 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/20 17:35:21 by sylewis          ###   ########.fr       */
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
	if (keycode == 84 || keycode == 19 || keycode == 91 || keycode == 28)
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
		printf("x = %d ", x);
		printf("y = %d\n", y);
		info->cam->offsetx -= x / (WIN_SIZE_X - HUD_SIZE) * (info->cam->zoom - 1);
		printf("offsetx = %f ", info->cam->offsetx);
		info->cam->offsety -= y / (WIN_SIZE_Y) * (info->cam->zoom - 1);
		printf("offsety = %f\n", info->cam->offsety);
		info->mouse->button = DOWN_WHEEL;
		info->cam->zoom -= 20;
		info->cam->speed += 0.25;
		if (info->cam->zoom < 1)
			info->cam->zoom = 1;
	}
	else if (button == UP_WHEEL)
	{
		printf("x = %d ", x);
		printf("y = %d\n", y);
		info->cam->offsetx -= x / (WIN_SIZE_X - HUD_SIZE) * (info->cam->zoom - 1);
		printf("offsetx = %f ", info->cam->offsetx);
		info->cam->offsety -= y / (WIN_SIZE_Y) * (info->cam->zoom - 1);
		printf("offsety = %f\n", info->cam->offsety);
		info->mouse->button = UP_WHEEL;
		info->cam->zoom += 20;
		info->cam->speed += 0.25;
		info->mouse->lastx = info->mouse->x;
		info->mouse->lasty = info->mouse->y;
	}
	if (info->mouse->button == 4 || info->mouse->button == 5)
		update_display(info);
	return (0);
}

int			mouse_release(int button, int x, int y, t_info *info)
{
	(void)x;
	(void)y;
	if (button == LEFT_CLICK)
		info->mouse->button = 0;
	if (button == RIGHT_CLICK)
		info->mouse->button2 = 0;
	//if (button == UP_WHEEL)
	//	info->mouse->button = 0;
	//if (button == DOWN_WHEEL)
	//	info->mouse->button = 0;
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
