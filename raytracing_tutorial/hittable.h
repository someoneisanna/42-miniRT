#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"

typedef union material material;

typedef struct hit_record
{
	point3 p;
	vec3 normal;
	float t;
	int front_face;
	material *material;
} hit_record;

void hit_set_face_normal(hit_record *rec, ray r, vec3 outward_normal)
{
	rec->front_face = vec3_dot(r.direction, outward_normal) < 0;
	rec->normal = rec->front_face ? outward_normal : vec3_mult_scalar(outward_normal, -1.0);
}

typedef struct sphere
{
	int type;
	point3 center;
	float radius;
	material *material;
} sphere;

int hit_sphere(sphere s, ray r, float t_min, float t_max, hit_record *rec)
{
	vec3 oc = vec3_sum(r.origin, vec3_mult_scalar(s.center, -1.0));
	float a = vec3_norm_squared(r.direction);
	float half_b = vec3_dot(oc, r.direction);
	float c = vec3_norm_squared(oc) - s.radius * s.radius;
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
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	rec->material = s.material;
	vec3 outward_normal = vec3_normalized(vec3_sum(rec->p, vec3_mult_scalar(s.center, -1.0)));
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
	int type;
	sphere sphere;
} hittable;

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