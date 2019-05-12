/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:00:13 by hcabel            #+#    #+#             */
/*   Updated: 2019/05/11 23:53:51 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h> // DEBUG

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_vector;

typedef struct		s_point
{
	struct s_vector	*v;
	struct s_point	*n1;
	struct s_point	*n2;
	int				n1_isprint;
	int				n2_isprint;
}					t_point;

typedef struct		s_map
{
	struct s_point	*start;
	int				max_z;
	int				min_z;
	int				nb_nb;
	int				size_y;
	int				size_x;
}					t_map;

typedef struct		s_mouse
{
	int				button;
	int				button2;
	int				x;
	int				y;
	int				lastx;
	int				lasty;
}					t_mouse;

typedef struct		s_img
{
	void			*ptr;
	char			*string;
	int				bpp;
	int				s_l;
	int				endian;
}					t_img;

typedef struct		s_info
{
	void			*mlx_ptr;
	void			*win_ptr;
	struct s_img	*img;
	struct s_map	*map;
	struct s_cam	*cam;
	struct s_mouse	*mouse;
}					t_info;

typedef struct		s_cam
{
	double			offsetx;
	double			offsety;
	double			x;
	double			y;
	double			zoom;
	double			speed;
	double			height_z;
	void			(*projection)(t_vector*, t_vector*, struct s_info*);
}					t_cam;

typedef struct		s_line
{
	struct s_vector	start;
	struct s_vector	stop;
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
	int				err2;
}					t_line;

# define FDF_END 0

/*
**	MODIFY here
*/
# define WIN_NAME "FDF by hcabel"
# define WIN_SIZE_X 1920
# define WIN_SIZE_Y 1080
# define HUD_SIZE 400
/*
**	HUD_SIZE IS BETTER >= 400
*/
# define HUD_BORDER_SIZE 5
/*
**	To here
*/

# define UP_WHEEL 4
# define DOWN_WHEEL 5
# define RIGHT_CLICK 2
# define LEFT_CLICK 1

# define ESC 53
# define UP 126
# define DOWN 125
# define SPACE 49

# define RED_CROSS 17
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define MOUSE_PRESS 4
# define MOUSE_RELEASE 5
# define MOUSE_MOVE 6

/*
**	action.c
*/
int					key_press(int keycode, t_info *info);
int					key_release(int keycode, t_info *info);
int					mouse_press(int button, int x, int y, t_info *info);
int					mouse_release(int button, int x, int y, t_info *info);
int					mouse_move(int x, int y, t_info *info);

/*
**	struct.c
*/
t_vector			*init_vector(double x, double y, double z);
t_vector			*cp_vector(t_vector v2);
t_map				*init_map(char *argv);
t_point				*newlink(t_vector *v);

/*
**	struct2.c
*/
t_info				*init_info(char *argv);
t_mouse				*init_mouse(void);
t_cam				*init_cam(void);

/*
**	parsing.c
*/
t_point				*parsing(t_map *map, int fd);

/*
**	projection.c
*/
void				parallele_view(t_vector *start, t_vector *end,
						t_info *info);
void				isometric_view(t_vector *start,  t_vector *end,
						t_info *info);

/*
**	main.c
*/
int					finish(char *reason);

/*
**	display_map.c
*/
void				updade_display(t_info *info);
void				reset_link(int n, t_point *current, t_info *info);
void				execute_link(int n, t_point *current, t_info *info);

/*
**	line.c
*/
void				line_trace(t_vector start, t_vector end, t_info *info);


/*
**	image.c
*/
t_img				*del_image(t_info *info);
void				fill_pixel(t_img *image, int x, int y, int color);
t_img				*init_image(t_info *info);

/*
**	color.c
*/
double 				get_percent(int start, int end, int current);
int					set_color(int c1, int c2, double percent);

/*
**	HUD.c
*/
void				add_hud(char **string);
void				add_hud_string(t_info *info);

#endif