#ifndef VEC3_H
#define VEC3_H

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

vec3 vec3_sum_scalar(vec3 vec, float a)
{
	return ((vec3) {vec.x + a, vec.y + a, vec.z + a});
}

vec3 vec3_mult_scalar(vec3 vec, float a)
{
	return ((vec3) {vec.x * a, vec.y * a, vec.z * a});
}

vec3 vec3_sum(vec3 vec1, vec3 vec2)
{
	return ((vec3) {vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

float vec3_norm_squared(vec3 vec)
{
	return(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float vec3_norm(vec3 vec)
{
	return(sqrt(vec3_norm_squared(vec)));
}

vec3 vec3_normalized(vec3 vec)
{
	float norm = vec3_norm(vec);
	return ((vec3) {vec.x / norm, vec.y / norm, vec.z / norm});
}

vec3 vec3_mult_element_wise(vec3 vec1, vec3 vec2)
{
	return ((vec3) {vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z});
}

float vec3_dot(vec3 vec1, vec3 vec2)
{
	return(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

int vec3_near_zero(vec3 vec)
{
	const float s = 1e-8;
	return ((fabs(vec.x) < s) && (fabs(vec.y) < s) && (fabs(vec.z) < s));
}

vec3 vec3_refract(vec3 uv, vec3 n, float etai_over_etat)
{
	float cos_theta = fmin (vec3_dot (vec3_mult_scalar (uv, -1.0), n), 1.0);
	vec3 cos_theta_n = vec3_mult_scalar (n, cos_theta);
	vec3 r_out_perp = vec3_mult_scalar (vec3_sum (uv, cos_theta_n), etai_over_etat);
	vec3 r_out_parallel = vec3_mult_scalar (n, -sqrt (fabsf ((float) 1. - vec3_norm_squared (r_out_perp))));
	return vec3_sum (r_out_perp, r_out_parallel);
}

vec3 vec3_reflect(vec3 v, vec3 n)
{
	return vec3_sum (v, vec3_mult_scalar (n, -2 * vec3_dot (v, n)));
}

vec3 vec3_random(unsigned int *seed)
{
	return ((vec3) {random_float(seed), random_float(seed), random_float(seed)});
}

vec3 vec3_random_min_max(unsigned int *seed, float min, float max)
{
	return ((vec3) {random_float_min_max(seed, min, max), random_float_min_max(seed, min, max), random_float_min_max(seed, min, max)});
}

vec3 vec3_random_in_unit_sphere(unsigned int *seed)
{
	while (1)
	{
		vec3 p = vec3_random_min_max(seed, -1, 1);
		if (vec3_norm_squared(p) >= 1)
			continue;
		return p;
	}
}

vec3 vec3_random_unit_vector(unsigned int *seed)
{
	return vec3_normalized(vec3_random_in_unit_sphere(seed));
}

vec3 vec3_random_in_hemisphere(vec3 normal, unsigned int *seed)
{
	vec3 in_unit_sphere = vec3_random_in_unit_sphere(seed);
	if (vec3_dot(in_unit_sphere, normal) > 0.0)
		return in_unit_sphere;
	else
		return vec3_mult_scalar(in_unit_sphere, -1);
}

void print_vec3(FILE *restrict __stream, vec3 vec)
{
	fprintf(__stream, "%.2f %.2f %.2f\n", vec.x, vec.y, vec.z);
}

#endif