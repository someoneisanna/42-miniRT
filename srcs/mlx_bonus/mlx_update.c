/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:46:26 by ataboada          #+#    #+#             */
/*   Updated: 2024/06/03 18:32:43 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_update(void *ptr)
{
	t_world	*w;

	w = (t_world *)ptr;
	if (w->status_key != 0)
	{
		w->img.img = mlx_new_image(w->mlx, w->camera->hsize, w->camera->vsize);
		w->img.addr = mlx_get_data_addr(w->img.img, &w->img.bpp,
				&w->img.line_length, &w->img.endian);
		ft_update_helper(w, w->status_key);
		ft_render_threads(w->camera, w);
		mlx_put_image_to_window(w->mlx, w->win, w->img.img, 0, 0);
	}
	return (0);
}

void	ft_update_helper(t_world *w, int key)
{
	t_shapes	*s;
	t_light		*l;

	s = (t_shapes *)w->objects->next->content;
	l = (t_light *)w->lights->content;
	if (w->oflag == 1)
	{
		s->transform = ft_update_shapes(s->transform, key);
		s->inverted = ft_invert_matrix(s->transform);
		s->transposed = ft_transpose_matrix(s->inverted);
	}
	else if (w->lflag == 1)
		ft_update_lights(l, key);
	else if (w->oflag == 0 && w->lflag == 0)
	{
		if (w->status_key != Z)
			w->camera->transform = ft_update_camera(w->camera->transform, key);
		else
			w->camera->transform = w->cam_reset;
		w->camera->inverted = ft_invert_matrix(w->camera->transform);
	}
}

t_matrix	ft_update_camera(t_matrix t, int key)
{
	if (key == W)
		t = ft_multiply_matrix(t, ft_rotation_matrix('x', M_PI / 18));
	else if (key == S)
		t = ft_multiply_matrix(t, ft_rotation_matrix('x', -M_PI / 18));
	else if (key == A)
		t = ft_multiply_matrix(t, ft_rotation_matrix('y', M_PI / 18));
	else if (key == D)
		t = ft_multiply_matrix(t, ft_rotation_matrix('y', -M_PI / 18));
	else if (key == UP)
		t = ft_multiply_matrix(t, ft_translation_matrix(0, -1, 0));
	else if (key == DOWN)
		t = ft_multiply_matrix(t, ft_translation_matrix(0, 1, 0));
	else if (key == LEFT)
		t = ft_multiply_matrix(t, ft_translation_matrix(1, 0, 0));
	else if (key == RIGHT)
		t = ft_multiply_matrix(t, ft_translation_matrix(-1, 0, 0));
	else if (key == SPACE)
		t = ft_multiply_matrix(t, ft_translation_matrix(0, 0, -1));
	else if (key == ALT)
		t = ft_multiply_matrix(t, ft_translation_matrix(0, 0, 1));
	else if (key == PLUS)
		t = ft_multiply_matrix(t, ft_scaling_matrix(1.3, 1.3, 1.3));
	else if (key == MINUS)
		t = ft_multiply_matrix(t, ft_scaling_matrix(0.7, 0.7, 0.7));
	return (t);
}

t_matrix	ft_update_shapes(t_matrix t, int key)
{
	if (key == W)
		t = ft_multiply_matrix(t, ft_rotation_matrix('x', -M_PI / 18));
	else if (key == S)
		t = ft_multiply_matrix(t, ft_rotation_matrix('x', M_PI / 18));
	else if (key == A)
		t = ft_multiply_matrix(t, ft_rotation_matrix('y', -M_PI / 18));
	else if (key == D)
		t = ft_multiply_matrix(t, ft_rotation_matrix('y', M_PI / 18));
	else if (key == UP)
		t = ft_multiply_matrix(t, ft_translation_matrix(0, 1, 0));
	else if (key == DOWN)
		t = ft_multiply_matrix(t, ft_translation_matrix(0, -1, 0));
	else if (key == LEFT)
		t = ft_multiply_matrix(t, ft_translation_matrix(-1, 0, 0));
	else if (key == RIGHT)
		t = ft_multiply_matrix(t, ft_translation_matrix(1, 0, 0));
	else if (key == ALT)
		t = ft_multiply_matrix(t, ft_translation_matrix(0, 0, 1));
	else if (key == SPACE)
		t = ft_multiply_matrix(t, ft_translation_matrix(0, 0, -1));
	else if (key == PLUS)
		t = ft_multiply_matrix(t, ft_scaling_matrix(1.3, 1.3, 1.3));
	else if (key == MINUS)
		t = ft_multiply_matrix(t, ft_scaling_matrix(0.7, 0.7, 0.7));
	return (t);
}

void	ft_update_lights(t_light *l, int key)
{
	if (key == UP)
		l->coordinates = ft_op(l->coordinates, '+', (t_point){0, -1, 0, 1});
	else if (key == DOWN)
		l->coordinates = ft_op(l->coordinates, '+', (t_point){0, 1, 0, 1});
	else if (key == LEFT)
		l->coordinates = ft_op(l->coordinates, '+', (t_point){-1, 0, 0, 1});
	else if (key == RIGHT)
		l->coordinates = ft_op(l->coordinates, '+', (t_point){1, 0, 0, 1});
	else if (key == ALT)
		l->coordinates = ft_op(l->coordinates, '+', (t_point){0, 0, 1, 1});
	else if (key == SPACE)
		l->coordinates = ft_op(l->coordinates, '+', (t_point){0, 0, -1, 1});
	else if (key == PLUS)
		l->intensity = ft_ops(l->intensity, '*', 1.3);
	else if (key == MINUS)
		l->intensity = ft_ops(l->intensity, '*', 0.7);
}
