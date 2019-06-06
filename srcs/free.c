/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:39:40 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/04 15:22:56 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_img(t_img *img)
{
	ft_memdel((void**)&(img->ptr));
	ft_memdel((void**)&(img->string));
	ft_memdel((void**)&img);
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
		ft_memdel((void**)&tmp->v);
		ft_memdel((void**)&tmp);
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
}

void		free_info(t_info *info)
{
	if (info->img != NULL)
		free_img(info->img);
	if (info->map != NULL)
		free_map(info->map);
	ft_memdel((void**)&info->cam);
	ft_memdel((void**)&info->mouse);
	ft_memdel((void**)&info->mlx_ptr);
	ft_memdel((void**)&info->win_ptr);
}
