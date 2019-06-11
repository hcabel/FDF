/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 10:31:54 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/09 18:39:50 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_point(char *ln)
{
	int i;
	int result;

	i = 0;
	result = 0;
	if (ft_isdigit(ln[i]))
		result = 1;
	while (ln[i])
	{
		if ((ln[i] == ' ' || ln[i] == '-') && ft_isdigit(ln[i + 1]))
			result++;
		i++;
	}
	return (result);
}
// problemes ici ? 
static int	check_hexa(char *ln, int i)
{
	int count;

	if (ln[i + 1] != '0' || ln[i + 2] != 'x')
		return (0);
	i += 3;
	count = 1;
	while (ft_isalnum(ln[i]) && ln[i] != ' ')
	{
	//	if (!((ln[i] >= '0' && ln[i] <= '9')
	//		|| (ln[i] >= 'A' && ln[i] <= 'F')
	//		|| (ln[i] >= 'a' && ln[i] <= 'f')))
		if ((ln[i] <= 'F' && ln[i] <= 'a') || ln[i] <= 'f')
			return (0);
		if (count > 6)
			return (0);
		count++;
		i++;
	}
	return (1);
}
// problemes ici ^ ?
static int	check_write(char *ln, t_info *info)
{
	int i;

	i = 0;
	while (!ft_isdigit(ln[i]))
		i++;
	if (!ft_isdigit(ln[i]))
		return (0);
	i = 0;
	while (ln[i])
	{
		while ((ln[i] == ' ' || ln[i] == '-') && ln[i])
			i++;
		if (!ft_isdigit(ln[i]))
			return (0);
		while (ft_isdigit(ln[i]))
			i++;
		if (!ln[i])
			break ;
		if (ln[i] == ',')
		{
			if (!check_hexa(ln, i))
				finish(info, "Your hexa is not good");
			while (ln[i] != ' ' && ln[i] != '\0' && ln[i] != '\n')
				i++;
		}
		else if (ln[i] != ' ' && ln[i] != '\0' && ln[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int			check_file(char *ln, t_map *map, t_info *info)
{
	int		tmp;

	if (ln[0] == '\n' || ln[0] == '\0')
		finish(info, "Map error! {- a line is empty -}");
	//if (ln[0] == ' ')
	//	finish(info, "Error map ! {- a line start with ' ' -}");
	if (!check_write(ln, info))
		finish(info, "Map error!");
	tmp = count_point(ln);
	if (tmp != map->nb_nb && map->nb_nb != -1)
		finish(info, "Map error! {- Differing numbers of points per line-}");
	map->nb_nb = tmp;
	return (0);
}
