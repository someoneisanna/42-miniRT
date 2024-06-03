/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:34:52 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/30 17:19:44 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Initializes a t_pattern struct with the given type and colors.
t_pattern	ft_create_pattern(char pattern_type, t_color a, t_color b)
{
	t_pattern	pattern;

	if (pattern_type == 'N')
		pattern.type = NONE;
	else if (pattern_type == 'T')
		pattern.type = TEST;
	else if (pattern_type == 'S')
		pattern.type = STRIPES;
	else if (pattern_type == 'G')
		pattern.type = GRADIENT;
	else if (pattern_type == 'R')
		pattern.type = RING;
	else if (pattern_type == 'C')
		pattern.type = CHECKERS;
	else if (pattern_type == 'X')
		pattern.type = XPM;
	else
		ft_perror(NULL, "Invalid pattern type");
	pattern.a = a;
	pattern.b = b;
	pattern.transform = ft_create_matrix(4, 4, YES);
	pattern.inverted = ft_create_matrix(4, 4, YES);
	pattern.xpm = (t_canvas){0};
	return (pattern);
}

// Returns the color of the pattern at the specified point.
t_color	ft_pattern_at_shape(t_pattern p, t_shapes *object, t_point world_point)
{
	t_point	object_pt;
	t_point	pattern_pt;

	object_pt = ft_multiply_matrix_tuple(object->inverted, world_point);
	pattern_pt = ft_multiply_matrix_tuple(p.inverted, object_pt);
	if (p.type == TEST)
		return ((t_color){pattern_pt.x, pattern_pt.y, pattern_pt.z, 3});
	else if (p.type == STRIPES)
		return (ft_stripe_at(p, object->type, pattern_pt));
	else if (p.type == GRADIENT)
		return (ft_gradient_at(p, pattern_pt));
	else if (p.type == RING)
		return (ft_ring_at(p, object->type, pattern_pt));
	else if (p.type == CHECKERS)
		return (ft_checkers_at(p, object->type, pattern_pt));
	else if (p.type == XPM)
		return (ft_xpm_at(p, pattern_pt));
	return ((t_color){0, 0, 0, 3});
}
