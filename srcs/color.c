/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:00:13 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/18 13:59:39 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	char2int(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (ch - '0');
	if (ch >= 'A' && ch <= 'F')
		return (ch - 'A' + 10);
	if (ch >= 'a' && ch <= 'f')
		return (ch - 'a' + 10);
	return (-1);
}

int			hexa2int(char *hexa, t_info *info)
{
	int	i;
	int	result;

	if (hexa[0] != '0' || hexa[1] != 'x')
		finish(info, "Hexa error");
	i = 2;
	while (hexa[i] == '0')
		i++;
	result = char2int(hexa[i]);
	if (result == -1)
		return (-1);
	i++;
	while (((hexa[i] >= '0' && hexa[i] <= '9')
		|| (hexa[i] >= 'A' && hexa[i] <= 'F')
		|| (hexa[i] >= 'a' && hexa[i] <= 'f')) && i < 9)
		result = result * 16 + char2int(hexa[i++]);
	return (result);
}

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
/*merge get_light et set_colour ? */
static int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}
/* merge ? */
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

void		colour_palette(t_cam *cam)
{
	cam->palette[0][0] = 0xff66ff;
	cam->palette[0][1] = 0x33ccff;
	cam->palette[1][0] = 0xffff66;
	cam->palette[1][1] = 0x00ff66;
	cam->palette[2][0] = 0xfb2d60;
	cam->palette[2][1] = 0x4ca7ad;
	cam->palette[3][0] = 0x555e58;
	cam->palette[3][1] = 0x872939;
	cam->palette[4][0] = 0xffd9d9;
	cam->palette[4][1] = 0xce0000;
	cam->palette[5][0] = 0x3b80f0;
	cam->palette[5][1] = 0x7b0b9b;
	cam->palette[6][0] = 0x6d1950;
	cam->palette[6][1] = 0xbd5f45;
	cam->palette[7][0] = 0x307c99;
	cam->palette[7][1] = 0xf07c99;
	cam->palette[8][0] = 0x7cd861;
	cam->palette[8][1] = 0xff839b;
	cam->palette[9][0] = 0xff66cc;
	cam->palette[9][1] = 0x26e8cc;
}
