/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:33:49 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/30 17:16:02 by ataboada         ###   ########.fr       */
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
	if (ft_in_range(w->ambient.color, 0, 1) == false)
		ft_perror(w, "Ambient color is not valid");
	return (count);
}

int	ft_get_camera(char *line, t_world *w)
{
	t_point		coordinates;
	t_vec3		orientation;
	double		fov;
	static int	count;

	line++;
	count++;
	if (count > 1)
		ft_perror(w, "Multiple cameras are not allowed");
	coordinates = ft_get_tuple(w, &line, 1);
	orientation = ft_get_tuple(w, &line, 0);
	if (ft_in_range(orientation, -1, 1) == false)
		ft_perror(w, "Camera orientation is not valid");
	fov = ft_atof(w, line);
	if (fov < 0 || fov > 180)
		ft_perror(w, "Camera fov is not valid");
	w->camera = ft_create_camera(w->width, w->height, fov * DEG2RAD);
	w->camera->transform = ft_view_transform_matrix(coordinates,
			ft_op(orientation, '+', coordinates), (t_point){0, 1, 0, 0});
	w->camera->inverted = ft_invert_matrix(w->camera->transform);
	return (count);
}

int	ft_get_light(char *line, t_world *w)
{
	t_light		*light;
	t_point		coordinates;
	double		brightness;
	static int	count;

	line++;
	count++;
	light = malloc(sizeof(t_light));
	if (!light)
		ft_perror(w, "Memory allocation of light failed");
	if (count > 1)
		ft_perror(w, "Multiple lights are not allowed");
	coordinates = ft_get_tuple(w, &line, 1);
	brightness = ft_get_double(w, &line, ' ');
	if (brightness < 0 || brightness > 1)
		ft_perror(w, "Light brightness is not valid");
	light->coordinates = coordinates;
	light->intensity = ft_ops((t_color){1, 1, 1, 3}, '*', brightness);
	w->lights = ft_lstnew(light);
	return (count);
}
