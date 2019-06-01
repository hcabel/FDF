/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:46:05 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/01 14:26:33 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				finish(t_info *info, char *reason)
{
	if (info != NULL)
		free_info(info);
	if (*reason == '\0')
		ft_putendl("usage : ./fdf [sourcesfile] [hexa color]");
	else
		ft_putendl_fd(reason, 2);
	exit(0);
	return (0);
}

int				main(int argc, char **argv)
{
	t_info	*info;

	info = NULL;
	if (argc < 2 || argc > 3)
		finish(info, "");
	info = init_info(argc, argv);
	update_display(info);
	mlx_hook(info->win_ptr, RED_CROSS, 0, finish, "End !");
	mlx_hook(info->win_ptr, KEY_PRESS, 0, key_press, info);
	mlx_hook(info->win_ptr, KEY_RELEASE, 0, key_release, info);
	mlx_hook(info->win_ptr, MOUSE_PRESS, 0, mouse_press, info);
	mlx_hook(info->win_ptr, MOUSE_RELEASE, 0, mouse_release, info);
	mlx_hook(info->win_ptr, MOUSE_MOVE, 0, mouse_move, info);
	mlx_loop(info->mlx_ptr);
	if (info != NULL)
		free_info(info);
	return (0);
}
