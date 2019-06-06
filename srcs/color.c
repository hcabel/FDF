/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:00:13 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/04 15:49:18 by sylewis          ###   ########.fr       */
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

static int	addcolour_topalette(int **tab, int i, int colour1, int colour2)
{
	if (!(tab[i] = (int*)ft_memalloc(sizeof(int) * 2)))
		return (1);
	tab[i][0] = colour1;
	tab[i][1] = colour2;
	return (0);
}

int			**colour_palette(t_info *info)
{
	int **tab;
	int	i;
	int	ret;

	if (!(tab = (int**)ft_memalloc(sizeof(int*) * 10)))
		finish(info, "Allocation failed");
	i = 0;
	ret = 0;
	ret += addcolour_topalette(tab, i++, 0xff66ff, 0x33ccff);
	ret += addcolour_topalette(tab, i++, 0xffff66, 0x00ff66);
	ret += addcolour_topalette(tab, i++, 0xfb2d60, 0x4ca7ad);
	ret += addcolour_topalette(tab, i++, 0x555e58, 0x872939);
	ret += addcolour_topalette(tab, i++, 0xffd9d9, 0xce0000);
	ret += addcolour_topalette(tab, i++, 0x3b80f0, 0x7b0b9b);
	ret += addcolour_topalette(tab, i++, 0x6d1950, 0xbd5f45);
	ret += addcolour_topalette(tab, i++, 0x307c99, 0xf07c99);
	ret += addcolour_topalette(tab, i++, 0x7cd861, 0xff839b);
	ret += addcolour_topalette(tab, i++, 0xff66cc, 0x26e8cc);
	if (ret != 0)
		finish(info, "Allocation failed");
	return (tab);
}
/*
int		**colour_palette(t_cam *cam)
{
	int tab[10][2];

	tab[0][0] = 0xff66ff;
	tab[0][1] = 0x33ccff;
	tab[1][0] = 0xffff66;
	tab[1][1] = 0x00ff66;
	tab[2][0] = 0xfb2d60;
	tab[2][1] = 0x4ca7ad;
	tab[3][0] = 0x555e58;
	tab[3][1] = 0x872939;
	tab[4][0] = 0xffd9d9;
	tab[4][1] = 0xce0000;
	tab[5][0] = 0x3b80f0;
	tab[5][1] = 0x7b0b9b;
	tab[6][0] = 0x6d1950;
	tab[6][1] = 0xbd5f45;
	tab[7][0] = 0x307c99;
	tab[7][1] = 0xf07c99;
	tab[8][0] = 0x7cd861;
	tab[8][1] = 0xff839b;
	tab[9][0] = 0xff66cc;
	tab[9][1] = 0x26e8cc;
	return (tab);
}
*/