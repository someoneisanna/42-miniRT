/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:33:49 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/30 17:39:25 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_get_ambient(char *line, t_world *w)
{
	static int	count;

	line++;
	count++;
	if (count > 1)
		ft_perror(w, "Multiple ambient lights are not allowed");
	w->ambient.ratio = ft_get_double(w, &line, ' ');
	if (w->ambient.ratio < 0 || w->ambient.ratio > 1)
		ft_perror(w, "Ambient ratio is not valid");
	w->ambient.color = ft_get_tuple(w, &line, 3);
	return (count);
}

int	ft_get_camera(char *line, t_world *w)
{
	static int	count;

	line++;
	count++;
	if (count > 1)
		ft_perror(w, "Multiple cameras are not allowed");
	w->cam_coords = ft_get_tuple(w, &line, 1);
	w->cam_orient = ft_get_tuple(w, &line, 0);
	if (ft_in_range(w->cam_orient, -1, 1) == false)
		ft_perror(w, "Camera orientation is not valid");
	w->cam_fov = ft_atof(w, line);
	if (w->cam_fov < 0 || w->cam_fov > 180)
		ft_perror(w, "Camera fov is not valid");
	return (count);
}

int	ft_get_light(char *line, t_world *w)
{
	t_light		*light;
	t_point		coordinates;
	t_color		color;
	double		brightness;

	line++;
	w->ui.n_li++;
	light = malloc(sizeof(t_light));
	if (!light)
		ft_perror(w, "Memory allocation of light failed");
	coordinates = ft_get_tuple(w, &line, 1);
	brightness = ft_get_double(w, &line, ' ');
	if (brightness < 0 || brightness > 1)
		ft_perror(w, "Light brightness is not valid");
	color = ft_get_tuple(w, &line, 3);
	light->coordinates = coordinates;
	light->intensity = ft_ops(color, '*', brightness);
	ft_lstadd_back(&w->lights, ft_lstnew(light));
	return (1);
}

void	ft_get_resolution(char *line, t_world *w)
{
	static int	count;
	double		ratio;

	line++;
	count++;
	if (count > 1)
		ft_perror(w, "Multiple resolutions are not allowed");
	w->width = ft_get_double(w, &line, ' ');
	ratio = ft_get_double(w, &line, ' ');
	w->height = w->width / ratio;
	if (w->width < 0 || w->height < 0)
		ft_perror(w, "Resolution is not valid");
}

void	ft_get_triangle(char *line, t_world *w)
{
	t_shapes	*s;

	line += 2;
	w->ui.n_tr++;
	s = ft_create_shape(TRIANGLE);
	s->triangle.p1 = ft_get_tuple(w, &line, 1);
	s->triangle.p2 = ft_get_tuple(w, &line, 1);
	s->triangle.p3 = ft_get_tuple(w, &line, 1);
	s->triangle.e1 = ft_op(s->triangle.p2, '-', s->triangle.p1);
	s->triangle.e2 = ft_op(s->triangle.p3, '-', s->triangle.p1);
	s->triangle.normal = ft_normalize(ft_cross(s->triangle.e2, s->triangle.e1));
	ft_get_texture(w, s, &line);
	s->material.ambient = ft_ops(w->ambient.color, '*', w->ambient.ratio);
	ft_add_shapes(&w->objects, s);
}
