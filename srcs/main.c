/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:46:05 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/18 11:41:52 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				finish(char *reason)
{
	if (*reason == '\0')
		ft_putendl("usage : ./fdf sourcesfile  |  exemple ./fdf maps/42.fdf");
	else
		ft_putendl_fd(reason, 2);
	exit(0);
	return (0);
}

static void	print_test(t_point *start)
{
	printf("%d ", (int)start->v->z);
	while (start->n1)
	{
		start = start->n1;
		printf("%d ", (int)start->v->z);
	}
	printf("\n");
	while (start->n2)
	{
		start = start->n2;
		printf("%d ", (int)start->v->z);
	}
	printf("\n");
}

int				main(int argc, char **argv)
{
	t_info	*info;

	if (argc != 2)
		finish("");
	info = init_info(argv[1]);
	print_test(info->map->start);
	updade_display(info);
	mlx_hook(info->win_ptr, RED_CROSS, 0, finish, "End !");
	mlx_hook(info->win_ptr, KEY_PRESS, 0, key_press, info);
	mlx_hook(info->win_ptr, KEY_RELEASE, 0, key_release, info);
	mlx_hook(info->win_ptr, MOUSE_PRESS, 0, mouse_press, info);
	mlx_hook(info->win_ptr, MOUSE_RELEASE, 0, mouse_release, info);
	mlx_hook(info->win_ptr, MOUSE_MOVE, 0, mouse_move, info);
	mlx_loop(info->mlx_ptr);
	return (0);
}
