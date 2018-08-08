/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_linux.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:23:07 by osamoile          #+#    #+#             */
/*   Updated: 2018/06/12 16:24:39 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H# define FDF_H
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_ARROW_UP 116
# define KEY_ARROW_DOWN 121
# define KEY_BACKSPACE 51
# define KEY_H 4
# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
# define ALPHA_HEIGHT 22
# define ALPHA_WIDTH 10
# define EVENT_KEYS 2
# define EVENT_CLOSE 17
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_vector;

typedef struct	s_bresenham
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		d;
	int		d1;
	int		d2;
}				t_bresenham;

typedef struct	s_img
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*img;
	char		*img_ptr;
}				t_img;

typedef struct	s_view
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_vector	**base;
	t_vector	**mod;
	int			rows;
	int			columns;
	int			angle_x;
	int			angle_y;
	int			angle_z;
	int			zoom;
	float		height;
	int			move_x;
	int			move_y;
	int			help;
	t_img		img;
}				t_view;

void			draw(t_view *view);
int				rgb_to_color(unsigned char r, unsigned char g, unsigned char b);
void			pixel_put_img(t_view *view, int x, int y, int color);
t_view			init(char *file);
void			default_settings(t_view *view);
void			intro(t_view *view);
void			help(t_view *view);
void			frame(t_view *view);
void			frame_labels(t_view *view);
int				key_hook(int key, void *v);
void			error(char *message);
void			line(t_view *view, t_vector dot1, t_vector dot2);
void			parse(char *file, t_vector **base, int x, int y);
int				get_x(char *file);
int				get_y(char *file);
void			transformation(t_view *view);

#endif
