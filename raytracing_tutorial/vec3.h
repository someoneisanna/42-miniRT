#ifndef VEC3_H
#define VEC3_H

#define YES 1
#define NO 0

#include <stdio.h>
#include <math.h>
#include "utils.h"

typedef struct vec3
{
	union 
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		struct
		{
			float r;
			float g;
			float b;
		};
	};
} vec3;

typedef vec3 point3;
typedef vec3 color;

// vector with vector operations
vec3 ft_op(vec3 vec1, char op, vec3 vec2)
{
	if (op == '+')
		return ((vec3) {vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
	else if (op == '-')
		return ((vec3) {vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
	else if (op == '*')
		return ((vec3) {vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z});
	else
		return ((vec3) {0, 0, 0});
}

// vector with scalar operations
vec3 ft_ops(vec3 vec, char op, float a)
{
	if (op == '+')
		return ((vec3) {vec.x + a, vec.y + a, vec.z + a});
	else if (op == '-')
		return ((vec3) {vec.x - a, vec.y - a, vec.z - a});
	else if (op == '*')
		return ((vec3) {vec.x * a, vec.y * a, vec.z * a});
	else
		return ((vec3) {0, 0, 0});
}

// the dot product of two vectors. normally used to calculate the 
// angle between two vectors
float ft_dot(vec3 vec1, vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

// normalized vector: vector that has been scaled to have a length of 1
// the normalized vector is given by: v / ||v||
vec3 ft_normalized(vec3 vec)
{
	// vector norm: measure of a vector's length (||v||)
	// the euclidean norm is given by: ||v|| = sqrt(vx² + vy² + vz²)
	float norm;
	
	norm = sqrt(ft_dot(vec, vec));
	return ((vec3) {vec.x / norm, vec.y / norm, vec.z / norm});
}

int ft_near_zero(vec3 vec)
{
	const float s = 1e-8;
	return ((fabs(vec.x) < s) && (fabs(vec.y) < s) && (fabs(vec.z) < s));
}

// dielectric materials use Snell's law to calculate the refraction of a ray
vec3 ft_refract(vec3 uv, vec3 n, float etai_over_etat)
{
	float cos_theta = fmin (ft_dot(ft_ops(uv, '*', -1.0), n), 1.0);
	vec3 cos_theta_n = ft_ops (n, '*', cos_theta);
	vec3 r_out_perp = ft_ops (ft_op(uv, '+', cos_theta_n), '*', etai_over_etat);
	vec3 r_out_parallel = ft_ops(n, '*', -sqrt (fabsf ((float) 1. - ft_dot(r_out_perp, r_out_perp))));
	return ft_op(r_out_perp, '+', r_out_parallel);
}

// reflection of a vector is the vector that results from flipping a vector 
// over a surface
vec3 ft_reflect(vec3 v, vec3 n)
{
	return ft_op(v, '+', ft_ops(n, '*', (-2 * ft_dot (v, n))));
}

vec3 ft_random(unsigned int *seed, float min, float max)
{
	if (min == 0 && max == 0)
		return ((vec3) {random_float (seed), random_float (seed), random_float (seed)});
	else
		return ((vec3) {random_float_min_max (seed, min, max), random_float_min_max (seed, min, max), random_float_min_max (seed, min, max)});
}

// generates a random point in a sphere of radius 1
// if the point is outside the sphere, it will generate another point
vec3 ft_random_in_unit_sphere(unsigned int *seed)
{
	while (1)
	{
		vec3 p = ft_random(seed, -1, 1);
		if (ft_dot(p, p) >= 1)
			continue;
		return p;
	}
}

// this is a helper function to help with Lambertian reflection. we are picking
// a random point on the surface of the unit sphere and then normalizing it.
vec3 ft_random_unit_vector(unsigned int *seed)
{
	return ft_normalized(ft_random_in_unit_sphere(seed));
}

#endif