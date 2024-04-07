#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray
{
	point3 origin;
	vec3 direction;
} ray;

point3 ray_at(ray ray, float t)
{
	point3 ret = ft_op(ray.origin, '+', ft_ops(ray.direction, '*', t));
	return ret;
}

#endif