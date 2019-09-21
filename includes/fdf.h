/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:00:13 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/21 19:07:23 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"

/*
**	MODIFY here
*/
# define W_NAME "FDF by hcabel & sylewis"
# define W_WID 1920
# define W_HEIGHT 1080
# define HUD_WID 1600

typedef struct		s_map
{
	int				biggest;
	int				lower;
	int				heigth;
	int				width;
	int				**map;
}					t_map;

typedef struct		s_object
{
	int				palette[10][2];
	int				index;
	double			offset_x;
	double			offset_y;
	double			rot_x;
	double			rot_y;
	double			zoom;
	double			height_z;
	double			colormidline;
}					t_object;

typedef struct		s_img
{
	void			*ptr;
	char			*string;
	int				bpp;
	int				s_l;
	int				endian;
}					t_img;

typedef struct		s_mouse
{
	int				button;
	int				last_x;
	int				last_y;
	int				current_x;
	int				current_y;
}					t_mouse;

typedef struct		s_info
{
	void			*mlx_ptr;
	void			*win_ptr;
	struct s_map	map;
	struct s_img	view;
	struct s_img	hud;
	struct s_object	obj;
	struct s_mouse	mouse;
}					t_info;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
	int				colour;
}					t_vector;

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

# define SETUP_ERROR 1
# define SETUP_GOOD 0
# define PARSING_KO 1
# define PARSING_OK 0

# define UP_WHEEL 4
# define RIGHT_CLICK 2
# define DOWN_WHEEL 5
# define LEFT_CLICK 1

# define ESC 53
# define TWO 19
# define NUM_TWO 84
# define EIGHT 28
# define NUM_EIGHT 91
# define SPACE 49
# define UP 126
# define DOWN 125
# define W 13
# define S 1

# define RED_CROSS 17
# define KEY_PRESS 2
# define MOUSE_PRESS 4
# define MOUSE_RELEASE 5
# define MOUSE_MOVE 6

/*
**	main.c
*/
int					end(t_info *info);
int					mouse_press(int button, int x, int y, t_info *info);
int					mouse_release(int button, int x, int y, t_info *info);
int					mouse_move(int x, int y, t_info *info);

/*
**	input.c
*/
int					key_press(int keycode, t_info *info);

/*
**	parsing.c
*/
int					parse_map(t_info *info, char *argv);

/*
**	line.c
*/
void				line_trace(t_vector start, t_vector end, t_info *info);

/*
**	hud.c
*/
void				display_update_hud(t_info info);

/*
**	view.c
*/
void				display_update_view(t_info *info);

/*
**	color.c
*/
void				set_palette(int palette[10][2]);
double				get_percent(int start, int end, int current);
int					set_colour(int c1, int c2, double percent);

#endif
