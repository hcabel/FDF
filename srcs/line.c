/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:17:36 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/15 16:35:02 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static void	setpixel(t_info *info, t_vector *p1, t_line *l, double percent)
{
	if (p1->x < 0 || p1->x >= W_WID - HUD_WID || p1->y < 0 || p1->y >= W_HEIGHT)
		return ;
	*(int*)(info->view.string
		+ (((int)p1->x + (int)p1->y * (W_WID - HUD_WID)) * 4)) =
		set_colour(l->start.colour, l->stop.colour, percent);
}

static int	line_process_point(t_info *info, t_line *l, t_vector *p1)
{
	double	percent;

	percent = (l->dx > l->dy ? get_percent(l->start.x, l->stop.x, (int)p1->x)
		: get_percent(l->start.y, l->stop.y, (int)p1->y));
	setpixel(info, p1, l, percent);
	l->err2 = l->err;
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}
	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}

void		line_trace(t_vector start, t_vector end, t_info *info)
{
	t_line line;

	start.x = (int)start.x;
	end.x = (int)end.x;
	start.y = (int)start.y;
	end.y = (int)end.y;
	line.start = start;
	line.stop = end;
	line.dx = (int)abs((int)end.x - (int)start.x);
	line.sx = (int)start.x < (int)end.x ? 1 : -1;
	line.dy = (int)abs((int)end.y - (int)start.y);
	line.sy = (int)start.y < (int)end.y ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	if ((start.x < 0 || start.x >= (W_WID - HUD_WID) || start.y < 0
		|| start.y >= W_HEIGHT) && (end.x < 0 || end.x >= (W_WID - HUD_WID)
		|| end.y < 0 || end.y >= W_HEIGHT))
		return ;
	while (((int)start.x != (int)end.x || (int)start.y != (int)end.y))
		line_process_point(info, &line, &start);
}
