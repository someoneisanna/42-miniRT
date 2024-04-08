#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray
{
	point3	origin;
	vec3	direction;
} ray;

// ray is a function of the form p(t) = A + tb
// where p is the 3D position vector, A is the origin of the ray, b is the direction of the ray
// <--------|-------|------->
//  t=-1   t=0     t=1   t=2
//          A       b
point3 ray_at(ray ray, float t)
{
	point3 ret = ft_op(ray.origin, '+', ft_ops(ray.direction, '*', t));
	return ret;
}

#endif