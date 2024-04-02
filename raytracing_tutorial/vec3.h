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

vec3 vec3_reflect(vec3 v, vec3 n)
{
	return (vec3_sum(v, vec3_mult_scalar(n, -2 * vec3_dot(v, n))));
}

vec3 vec3_random()
{
	return ((vec3) {random_float(), random_float(), random_float()});
}

vec3 vec3_random_min_max(float min, float max)
{
	return ((vec3) {random_float_min_max(min, max), random_float_min_max(min, max), random_float_min_max(min, max)});
}

vec3 vec3_random_in_unit_sphere()
{
	while (1)
	{
		vec3 p = vec3_random_min_max(-1, 1);
		if (vec3_norm_squared(p) >= 1)
			continue;
		return p;
	}
}

vec3 vec3_random_unit_vector()
{
	return vec3_normalized(vec3_random_in_unit_sphere());
}

vec3 vec3_random_in_hemisphere(vec3 normal)
{
	vec3 in_unit_sphere = vec3_random_in_unit_sphere();
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