/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:55:39 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/30 16:25:51 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

// -------------------------------- INCLUDES -----------------------------------

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "minirt.h"

// --------------------------------- DEFINES -----------------------------------

# define ESC	65307
# define W		119
# define A		97
# define S		115
# define D		100
# define R		114
# define O		111
# define L		108
# define M		109
# define N		110
# define Z		122
# define UP		65362
# define DOWN	65364
# define LEFT	65361
# define RIGHT	65363
# define ALT	65513
# define SPACE	32
# define PLUS	65451
# define MINUS	65453

// -------------------------------- PROTOTYPES ---------------------------------

typedef struct s_image	t_image;
typedef struct s_world	t_world;

void		ft_open_window(t_world *w);
void		ft_panel_window(t_image *data, int x, int y, t_color **color);

void		ft_set_hooks(t_world *w);
int			ft_button_press(int keycode, t_world *w);
int			ft_button_release(int keycode, t_world *w);
int			ft_close(t_world *w);

// --------------------------------- BONUS -------------------------------------

void		ft_set_ui(t_world *w);
void		ft_set_arrays(t_world *w);
void		ft_free_ui(t_world *w);

int			ft_update(void *w);
void		ft_update_helper(t_world *w, int key);
t_matrix	ft_update_camera(t_matrix t, int key);
t_matrix	ft_update_shapes(t_matrix t, int key);
void		ft_update_lights(t_light *l, int key);

int			ft_clamp(int value, int min, int max);
int			ft_int_to_rgb(t_color color);
t_color		ft_rgb_to_int(int color);
void		ft_free_all_allocated_memory(t_world *w);

#endif
