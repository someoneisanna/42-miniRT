/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:41:03 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/13 14:57:32 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Calculates the color of the pixel at the specified coordinates.
t_color	ft_shade_hit(t_world *w, t_comps *c, t_material m, int remaining)
{
	t_color		surface;
	t_color		reflected;
	t_color		refracted;
	double		reflectance;
	t_list		*temp;

	surface = ft_op(m.color, '*', m.ambient);
	temp = w->lights;
	while (temp)
	{
		surface = ft_op(surface, '+', ft_lighting(c, temp->content,
					ft_is_shadowed(w, temp->content, c->over_point)));
		temp = temp->next;
	}
	reflected = ft_reflected_color(w, c, remaining);
	refracted = ft_refracted_color(w, c, remaining);
	if (m.reflective > 0 && m.transparency > 0)
	{
		reflectance = ft_schlick(c);
		return (ft_op(surface, '+', ft_op(ft_ops(reflected, '*', reflectance),
					'+', ft_ops(refracted, '*', (1 - reflectance)))));
	}
	return (ft_op(ft_op(surface, '+', reflected), '+', refracted));
}
