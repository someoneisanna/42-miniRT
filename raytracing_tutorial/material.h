#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "vec3.h"
#include "ray.h"

#include "hittable.h"

typedef struct lambertian
{
	int type;
	color albedo;
} lambertian;

#define LAMBERTIAN 1

lambertian create_lambertian(color albedo)
{
	lambertian ret = {0};
	ret.type = LAMBERTIAN;
	ret.albedo = albedo;
	return ret;
}

int lambertian_scatter(lambertian l, ray r, hit_record *rec, color *attenuation, ray *scattered)
{
	vec3 scatter_direction = vec3_sum(rec->normal, vec3_random_unit_vector());
	if (vec3_near_zero(scatter_direction))
		scatter_direction = rec->normal;
	ray new_r = {0};
	new_r.origin = rec->p;
	new_r.direction = scatter_direction;
	*scattered = new_r;
	*attenuation = l.albedo;
	return 1;
}

typedef struct metal
{
	int type;
	color albedo;
	float fuzz;
} metal;

#define METAL 2

metal create_metal(color albedo, float fuzz)
{
	metal ret = {0};
	ret.type = METAL;
	ret.albedo = albedo;
	ret.fuzz = fuzz < 1 ? fuzz : 1;
	return ret;
}

int metal_scatter(metal m, ray r, hit_record *rec, color *attenuation, ray *scattered)
{
	vec3 reflected = vec3_reflect(vec3_normalized(r.direction), rec->normal);
	ray new_r = {0};
	new_r.origin = rec->p;
	new_r.direction = vec3_sum(reflected, vec3_mult_scalar(vec3_random_in_unit_sphere(), m.fuzz));

	*scattered = new_r;
	*attenuation = m.albedo;
	return 1;
}

typedef union material
{
	int type;
	lambertian lambertian;
} material;

int material_scatter(material *m, ray r, hit_record *rec, color *attenuation, ray *scattered)
{
	switch (m->type)
	{
		case LAMBERTIAN:
			return lambertian_scatter(*(lambertian*) rec->material, r, rec, attenuation, scattered);
			break;
		case METAL:
			return metal_scatter(*(metal*) rec->material, r, rec, attenuation, scattered);
			break;
		default:
			return 0;
	}
}

#endif
