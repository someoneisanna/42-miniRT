#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "vec3.h"
#include "ray.h"

#include "hittable.h"

typedef enum
{
	LAMBERTIAN,
	METAL,
	DIELECTRIC,
	DIFFUSE_LIGHT
} materials;

typedef struct lambertian
{
	int type;
	color albedo;
} lambertian;

lambertian create_lambertian(color albedo)
{
	lambertian ret = {0};
	ret.type = LAMBERTIAN;
	ret.albedo = albedo;
	return ret;
}

int lambertian_scatter(lambertian l, ray r, hit_record *rec, color *attenuation, ray *scattered, unsigned int *seed)
{
	vec3 scatter_direction = ft_op(rec->normal, '+', ft_random_unit_vector(seed));
	if (ft_near_zero(scatter_direction))
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

metal create_metal(color albedo, float fuzz)
{
	metal ret = {0};
	ret.type = METAL;
	ret.albedo = albedo;
	ret.fuzz = fuzz < 1 ? fuzz : 1;
	return ret;
}

int metal_scatter(metal m, ray r, hit_record *rec, color *attenuation, ray *scattered, unsigned int *seed)
{
	vec3 reflected = ft_reflect(ft_normalized(r.direction), rec->normal);
	ray new_r = {0};
	new_r.origin = rec->p;
	new_r.direction = ft_op(reflected, '+', ft_ops(ft_random_in_unit_sphere(seed), '*', m.fuzz));

	*scattered = new_r;
	*attenuation = m.albedo;
	return 1;
}

typedef struct dielectric
{
	int type;
	float ir;
} dielectric;

dielectric create_dielectric(float ir)
{
	dielectric ret = {0.0};
	ret.type = DIELECTRIC;
	ret.ir = ir;
	return ret;
}

float reflectance(float cos, float ir)
{
	float r0 = (1. - ir) / (1. + ir);
	r0 *= r0;
	return r0 + (1 - r0) * pow ((1 - cos), 5);
}

int dielectric_scatter(dielectric d, ray r, hit_record *rec, color *attenuation, ray *scattered, unsigned int *seed)
{
	*attenuation = (color) { 1., 1., 1. };
	float refraction_ratio = rec->front_face ? (1.0) / d.ir : d.ir;

	vec3 unit_direction = ft_normalized(r.direction);
	float cos_theta = fmin (
	ft_dot(ft_ops(unit_direction, '*', -1.0), rec->normal), 1.0);
	float sin_theta = sqrt (1.0 - cos_theta * cos_theta);

	int cannot_refract = refraction_ratio * sin_theta > 1.0;
	vec3 direction = {0.0};
	if (cannot_refract || reflectance (cos_theta, refraction_ratio) > random_float (seed))
		direction = ft_reflect (unit_direction, rec->normal);
	else
		direction = ft_refract(unit_direction, rec->normal, refraction_ratio);
	*scattered = (ray) {rec->p, direction};
	return 1;
}

typedef struct diffuse_light
{
	int type;
	color emit;
} diffuse_light;

diffuse_light create_diffuse_light(color emit)
{
	diffuse_light ret = {0.0};
	ret.type = DIFFUSE_LIGHT;
	ret.emit = emit;
	return ret;
}

color diffuse_emit(diffuse_light light)
{
	return light.emit;
}

typedef union material
{
	int type;
	lambertian lambertian;
	metal metal;
	dielectric dielectric;
	diffuse_light diffuse_light;
} material;

int material_scatter(material *m, ray r, hit_record *rec, color *attenuation, ray *scattered, unsigned int *seed)
{
	switch (m->type)
	{
		case LAMBERTIAN:
			return lambertian_scatter(*(lambertian*)m, r, rec, attenuation, scattered, seed);
			break;
		case METAL:
			return metal_scatter(*(metal*)m, r, rec, attenuation, scattered, seed);
			break;
		case DIELECTRIC:
			return dielectric_scatter(*(dielectric*)m, r, rec, attenuation, scattered, seed);
			break;
		default:
			return 0;
	}
}

color material_emit(material *m)
{
	switch (m->type)
	{
		case DIFFUSE_LIGHT:
			return (diffuse_emit(*(diffuse_light*)m));
			break;
		default:
			return ((color) {0, 0, 0});
	}
}

#endif
