/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:32:36 by mamaral-          #+#    #+#             */
/*   Updated: 2024/04/17 15:11:09 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "box.h"
# include "hittable.h"
# include "libft.h"
# include "rays.h"
# include "vectors.h"
# include "scene.h"
# include <X11/X.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 800
# define RATIO 1.777777777777777777
# define SAMPLES_PER_PIXEL 100
# define MAX_DEPTH 50
# define TOP_BAR 55
# define BOTTOM_BAR 20
# define PI 3.1415926536

# define ESC 65307

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_color		**samp_color;
}				t_image;

typedef struct s_minirt
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_image		top_offset;
	t_image		bottom_offset;
	t_camera	cam;
	t_vec3		my_mouse;
	//t_scene		scene;
	bool		update_ui;
	bool		ready;
}				t_minirt;

//void			ft_mlx_pixel_put(t_minirt *data, int x, int y, int color);
//int				ft_close(t_minirt *test);

#endif