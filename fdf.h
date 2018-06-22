/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:23:07 by osamoile          #+#    #+#             */
/*   Updated: 2018/06/12 16:24:39 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

# define ESC 53
# define X_AXIS 0
# define Y_AXIS 1
# define Z_AXIS 3
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define W 13
# define A 0 // ???????????
# define S 1
# define D 2 // ?????????
# define PLUS 24
# define MINUS 27
# define HEIGHT 800
# define WIDTH 1500

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct	s_view
{
	void		*mlx_ptr;
	void		*win_ptr;
	
	t_vector	**base;
	int			rows;
	int			columns;

	int			angleX;
	int			angleY;
	int			angleZ;
	float		zoom;
	float		height;
	
}				t_view;


#endif
