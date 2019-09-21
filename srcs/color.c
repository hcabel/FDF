/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:00:13 by hcabel            #+#    #+#             */
/*   Updated: 2019/08/03 15:49:02 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		get_percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	if (start == end)
		return (start);
	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

static int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			set_colour(int c1, int c2, double percent)
{
	int red;
	int green;
	int blue;

	if (c1 == c2)
		return (c2);
	red = get_light((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, percent);
	green = get_light((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, percent);
	blue = get_light(c1 & 0xFF, c2 & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

void		set_palette(int palette[10][2])
{
	palette[0][0] = 0xff66ff;
	palette[0][1] = 0x33ccff;
	palette[1][0] = 0xffff66;
	palette[1][1] = 0x00ff66;
	palette[2][0] = 0xfb2d60;
	palette[2][1] = 0x4ca7ad;
	palette[3][0] = 0x555e58;
	palette[3][1] = 0x872939;
	palette[4][0] = 0xffd9d9;
	palette[4][1] = 0xce0000;
	palette[5][0] = 0x3b80f0;
	palette[5][1] = 0x7b0b9b;
	palette[6][0] = 0x6d1950;
	palette[6][1] = 0xbd5f45;
	palette[7][0] = 0x307c99;
	palette[7][1] = 0xf07c99;
	palette[8][0] = 0x7cd861;
	palette[8][1] = 0xff839b;
	palette[9][0] = 0xff66cc;
	palette[9][1] = 0x26e8cc;
}
