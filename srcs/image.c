/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:35:04 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/11 15:10:35 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img	*del_image(t_info *info)
{
	if (info->img != NULL)
	{
		if (info->img->ptr != NULL)
			mlx_destroy_image(info->mlx_ptr, info->img->ptr);
		ft_memdel((void **)&info->img);
	}
	return (NULL);
}

void	fill_pixel(t_img *image, int x, int y, int color)
{
	if (x < 400 || x >= WIN_SIZE_X || y < 0 || y >= WIN_SIZE_Y)
		return ;
	else
		*(int *)(image->string + ((x + y * WIN_SIZE_X) * 4)) = color;
}

t_img	*init_image(t_info *info)
{
	t_img	*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (0);
	img->ptr = mlx_new_image(info->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	img->string = mlx_get_data_addr(img->ptr,
		&img->bpp, &img->s_l, &img->endian);
	return (img);
}
