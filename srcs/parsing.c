/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:47:04 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/21 16:27:04 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void	get_smallest_and_biggest(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < info->map.heigth)
	{
		x = 0;
		while (x < info->map.width)
		{
			if (info->map.biggest == 0)
				info->map.biggest = info->map.map[y][x];
			if (info->map.lower == 0)
				info->map.lower = info->map.map[y][x];
			if (info->map.lower > info->map.map[y][x])
				info->map.lower = info->map.map[y][x];
			if (info->map.biggest < info->map.map[y][x])
				info->map.biggest = info->map.map[y][x];
			x++;
		}
		y++;
	}
}

static int	getinfo(t_info *info, char *line, int nbrline, void *ptr)
{
	int	i;

	(void)nbrline;
	i = 0;
	info->map.width = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if ((line[i] >= '0' && line[i] <= '9') || (line[i] == '-'
			&& (line[i + 1] >= '0' && line[i + 1] <= '9')))
			info->map.width++;
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
			i++;
		if (line[i] != ' ')
			while (line[i] && line[i] != ' ')
				i++;
	}
	if (info->map.width != *((int*)ptr) && info->map.heigth > 0)
		return (PARSING_KO);
	else
		*((int*)ptr) = info->map.width;
	info->map.heigth++;
	return (PARSING_OK);
}

static int	add_line_to_tab(t_info *info, char *line, int y, void *ptr)
{
	int	i;
	int	x;

	(void)ptr;
	if (!(info->map.map[y] = (int*)malloc(sizeof(int) * info->map.width)))
		return (PARSING_KO);
	x = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if ((line[i] >= '0' && line[i] <= '9') || (line[i] == '-'
			&& (line[i + 1] >= '0' && line[i + 1] <= '9')))
			info->map.map[y][x] = ft_atoi(line + i);
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
			i++;
		if (line[i] != ' ')
			while (line[i] && line[i] != ' ')
				i++;
		x++;
	}
	return (PARSING_OK);
}

static int	see_map(t_info *info, int fd, int (*f)(t_info*, char*, int, void*)
	, void *ptr)
{
	int		ret;
	char	*line;
	int		line_nbr;

	line_nbr = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (f(info, line, line_nbr, ptr))
		{
			free(line);
			return (PARSING_KO);
		}
		line_nbr++;
		free(line);
	}
	return (ret == -1 ? PARSING_KO : PARSING_OK);
}

int			parse_map(t_info *info, char *argv)
{
	int	previous_width;
	int	fd;

	if ((fd = open(argv, O_RDONLY)) == PARSING_KO)
		return (PARSING_KO);
	previous_width = 0;
	if (see_map(info, fd, getinfo, &previous_width) == PARSING_KO)
		return (PARSING_KO);
	close(fd);
	if ((fd = open(argv, O_RDONLY)) == PARSING_KO)
		return (PARSING_KO);
	if (!(info->map.map = (int**)malloc(sizeof(int*) * info->map.heigth)))
		return (PARSING_KO);
	if (see_map(info, fd, add_line_to_tab, NULL) == PARSING_KO)
		return (PARSING_KO);
	close(fd);
	get_smallest_and_biggest(info);
	return (PARSING_OK);
}
