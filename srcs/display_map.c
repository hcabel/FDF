/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:52:35 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/01 15:01:05 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	connect_point(t_point *current, t_info *info)
{
	static int i = 0;

	i++;
	if ((current->n1_isprint == 1 && current->n2_isprint == 1)
		|| (current->n1 == NULL && current->n2 == NULL))
		return ;
	else if (current->n1 != NULL && current->n2 == NULL
		&& current->n1_isprint == 0)
		execute_link(1, current, info);
	else if (current->n1 == NULL && current->n2 != NULL
		&& current->n2_isprint == 0)
		execute_link(2, current, info);
	else if (current->n1 != NULL && current->n2 != NULL)
	{
		if (current->n1_isprint == 0)
			execute_link(1, current, info);
		if (current->n2_isprint == 0)
			execute_link(2, current, info);
	}
}

static void	reset_point(t_point *current, t_info *info)
{
	if ((current->n1_isprint == 0 && current->n2_isprint == 0)
		|| (current->n1 == NULL && current->n2 == NULL))
		return ;
	else if (current->n1 != NULL && current->n2 == NULL
		&& current->n1_isprint == 1)
		reset_link(1, current, info);
	else if (current->n1 == NULL && current->n2 != NULL
		&& current->n2_isprint == 1)
		reset_link(2, current, info);
	else if (current->n1 != NULL && current->n2 != NULL)
	{
		if (current->n1_isprint == 1)
			reset_link(1, current, info);
		if (current->n2_isprint == 1)
			reset_link(2, current, info);
	}
}

void		reset_link(int n, t_point *current, t_info *info)
{
	if (n == 1)
	{
		current->n1_isprint = 0;
		reset_point(current->n1, info);
	}
	if (n == 2)
	{
		current->n2_isprint = 0;
		reset_point(current->n2, info);
	}
}

void		execute_link(int n, t_point *current, t_info *info)
{
	if (n == 1)
	{
		info->cam->projection(current->v, current->n1->v, info);
		current->n1_isprint = 1;
		connect_point(current->n1, info);
	}
	if (n == 2)
	{
		info->cam->projection(current->v, current->n2->v, info);
		current->n2_isprint = 1;
		connect_point(current->n2, info);
	}
}

void		update_display(t_info *info)
{
	ft_bzero(info->img->string, WIN_SIZE_X * WIN_SIZE_Y * 4);
	reset_point(info->map->start, info);
	info->map->biggest->colour = info->cam->colour_palette[info->cam->colour_modifier][0];
	info->map->smallest->colour = info->cam->colour_palette[info->cam->colour_modifier][1];
	connect_point(info->map->start, info);
	add_hud(&info->img->string, info);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->ptr, 0, 0);
	add_hud_string(info);
}
