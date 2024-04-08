#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"

typedef union material material;

//this is the struct used to store the information of the object that was hit
typedef struct hit_record
{
	point3		p;
	vec3		normal;
	float		t;
	int			front_face;
	material	*material;
} hit_record;

void hit_set_face_normal(hit_record *rec, ray r, vec3 outward_normal)
{
	// If the dot product of the ray direction and the normal is negative, 
	// it means the ray is hitting the object from the outside, and the normal
	// is pointing towards the ray. If it's positive, it means the ray is hitting
	// the object from the inside, and the normal is pointing away from the ray.
	rec->front_face = ft_dot(r.direction, outward_normal) < 0;

	// If the ray is hitting the object from the inside, we need to invert 
	// the normal to make it point towards the ray.
	rec->normal = rec->front_face ? outward_normal : ft_ops(outward_normal, '*', -1.0);
}

typedef struct sphere
{
	int			type;
	point3		center;
	float		radius;
	material	*material;
} sphere;

// this is where we check if the ray hits the sphere (in which case we color it
// with the sphere's material)
int hit_sphere(sphere s, ray r, float t_min, float t_max, hit_record *rec)
{
	// here, we are using two important formulas:
	// 1. x² + y² + z² = r²								(sphere equation)
	// 2. (x - Cx)² + (y - Cy)² + (z - Cz)² = r²		(sphere equation with center C)
	// 3. (x - Cx)² + (y - Cy)² + (z - Cz)² = (P - C)²	(vector from center to point P)
	// 2. P(t) = A + tB									(ray equation)
	// final equation -> B²t² + 2Bt(A - C) + (A - C)² - r² = 0

	vec3 oc = ft_op(r.origin, '-', s.center);			// A - C
	float a = ft_dot(r.direction, r.direction);			// B²
	float half_b = ft_dot(oc, r.direction);				// (A - C) * B
	float c = ft_dot(oc, oc) - s.radius * s.radius;		// (A - C)² - r²
	float discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return 0;
	float sqrtd = sqrt(discriminant);
	float root =  (-half_b - sqrtd) / a;
	if (root < t_min || root > t_max)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || root > t_max)
			return 0;
	}
	rec->t = root;					// t - distance from the ray origin to the hit point
	rec->p = ray_at(r, rec->t);		// p - hit point
	rec->material = s.material;

	// we need the outward normal to find out if the ray is inside or outside 
	// the sphere.
	vec3 outward_normal = ft_normalized(ft_op(rec->p, '-', s.center));

	// here we set the normal according to the ray direction
	hit_set_face_normal(rec, r, outward_normal);
	return 1;
}

#define SPHERE 1

sphere create_sphere(point3 center, float radius, material *material)
{
	sphere s = {0};
	s.type = SPHERE;
	s.center = center;
	s.radius = radius;
	s.material = material;
	return s;
}

typedef union hittable
{
	int		type;
	sphere	sphere;
} hittable;

// here we delegate the hit function to the specific object type
int hittable_hit(hittable h, ray r, float t_min, float t_max, hit_record *rec)
{
	switch (h.type)
	{
		case SPHERE:
			return (hit_sphere(*(sphere*) &h, r, t_min, t_max, rec));
			break;
		default:
			return 0;
	}
}

typedef struct hittable_list
{
	hittable *data;
	int size;
} hittable_list;

// in here, if we check if the ray hits any object in the list
// we use the closest_so_far to make sure we are only coloring the object that
// is closest to the camera, so it doesn't get covered by other objects.
int hittable_list_hit(hittable_list *hit_list, ray r, float t_min, float t_max, hit_record *rec)
{
	int hit_anything = 0;
	float closest_so_far = t_max;
	hit_record temp_rec;
	for (int i = 0; i < hit_list->size; i++)
	{
		hittable current = hit_list->data[i];
		if (hittable_hit(current, r, t_min, closest_so_far, &temp_rec))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}
	return hit_anything;
}

#endif