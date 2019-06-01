/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:17:36 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/01 14:43:20 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	line_process_point(t_info *info, t_line *l, t_vector *p1,
		t_vector *p2)
{
	double	percent;

	if ((p1->x < HUD_SIZE || p1->x >= WIN_SIZE_X
			|| p1->y < 0 || p1->y >= WIN_SIZE_Y)
		&& (p2->x < HUD_SIZE || p2->x >= WIN_SIZE_X
			|| p2->y < 0 || p2->y >= WIN_SIZE_Y))
		return (1);
	percent = (l->dx > l->dy ?
		get_percent(l->start.x, l->stop.x, (int)p1->x)
		: get_percent(l->start.y, l->stop.y, (int)p1->y));
	fill_pixel(info->img, (int)p1->x, (int)p1->y,
		set_colour(p1->colour, p2->colour, percent));
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
	while (((int)start.x != (int)end.x || (int)start.y != (int)end.y))
		if (line_process_point(info, &line, &start, &end))
			break ;
}
