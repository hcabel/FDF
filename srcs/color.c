/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:00:13 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/01 13:13:53 by hcabel           ###   ########.fr       */
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

static int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			set_color(int c1, int c2, double percent)
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

int			**color_palette(t_info *info)
{
	int **tab;

	if (!(tab = (int**)malloc(sizeof(int*) * 6)))
		finish(info, "Allocation failed");
	if (!(tab[0] = (int*)malloc(sizeof(int) * 2)))
		finish(info, "Allocation failed");
	tab[0][0] = 0xff66ff;
	tab[0][1] = 0x33ccff;
	if (!(tab[1] = (int*)malloc(sizeof(int) * 2)))
		finish(info, "Allocation failed");
	tab[1][0] = 0xffff66;
	tab[1][1] = 0x00ff66;
	if (!(tab[2] = (int*)malloc(sizeof(int) * 2)))
		finish(info, "Allocation failed");
	tab[2][0] = 0xfb2d60;
	tab[2][1] = 0x4ca7ad;
	if (!(tab[3] = (int*)malloc(sizeof(int) * 2)))
		finish(info, "Allocation failed");
	tab[3][0] = 0x555e58;
	tab[3][1] = 0x872939;
	if (!(tab[4] = (int*)malloc(sizeof(int) * 2)))
		finish(info, "Allocation failed");
	tab[4][0] = 0xffd9d9;
	tab[4][1] = 0xce0000;
	if (!(tab[5] = (int*)malloc(sizeof(int) * 2)))
		finish(info, "Allocation failed");
	tab[5][0] = 0x3b80f0;
	tab[5][1] = 0x7b0b9b;
	return (tab);
}