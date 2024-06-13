/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:23:23 by mamaral-          #+#    #+#             */
/*   Updated: 2024/04/17 14:42:46 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "minirt.h"

/*
int	ft_touch_sphere(t_sphere sphere, t_ray ray, double t_min, double t_max,
		t_hit_record *hit_record)
{
	t_vec3	oc;
	double	a;
	double	b_half;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
	t_vec3	outward_normal;

	oc = ft_op(ray.origin, '-', sphere.center);
	a = ft_dot(ray.direction, ray.direction);
	b_half = ft_dot(oc, ray.direction);
	c = ft_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b_half * b_half - a * c;
	if (discriminant < 0.)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (-b_half - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-b_half + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (0);
	}
	hit_record->t = root;
	hit_record->p = rayat(ray, hit_record->t);
	hit_record->material = sphere.material;
	outward_normal = ft_normalized(ft_op(hit_record->p, '-', sphere.center));
	ft_set_face_normal(hit_record, ray, outward_normal);
	return (1);
}

t_sphere	ft_create_sphere(t_point center, float radius, t_material *material)
{
	t_sphere	ret;

	ret = (t_sphere){0};
	ret.type = SPHERE;
	ret.center = center;
	ret.radius = radius;
	ret.material = material;
	return (ret);
}
*/