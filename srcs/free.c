/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:39:40 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/22 12:49:46 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_img(t_img *img)
{
	free(img->ptr);
	free(img->string);
	free(img);
}

static void	free_line(t_point *start)
{
	t_point	*tmp;
	t_point	*previous;

	while (start->n2)
	{
		tmp = start;
		previous = NULL;
		while (tmp->n2)
		{
			previous = tmp;
			tmp = tmp->n2;
		}
		previous->n2 = NULL;
		free(tmp->v);
		free(tmp);
	}
}

static void	free_chaine(t_map *map, t_point *start)
{
	int		max;

	max = map->nb_nb;
	while (max > 0)
	{
		free_line(getref(start, max, 0));
		max--;
	}
}

static void	free_map(t_map *map)
{
	if (map->start != NULL)
		free_chaine(map, map->start);
	free(map);
}

void	free_info(t_info *info)
{
	if (info->img != NULL)
		free_img(info->img);
	if (info->map != NULL)
		free_map(info->map);
	free(info->cam);
	free(info->mouse);
	free(info->mlx_ptr);
	free(info->win_ptr);
}