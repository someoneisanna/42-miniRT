// #include "rays.h"
#include "hittable.h"

/*
t_vec3	ft_def_viewp_top_lft(t_camera *camera, t_vec3 u, t_vec3 v, t_vec3 w)
{
	t_vec3	part1;
	t_vec3	part2;

	part1 = ft_op(ft_op(camera->pos, '-', ft_ops(w, '*', camera->focus_dist)), '-',
			ft_ops(ft_ops(u, '*', camera->viewp_w), '/' ,2));
	part2 = ft_ops(ft_ops(v, '*', -camera->viewp_h),'/' , 2);
	return (ft_op(part1, '-', part2));
}

void	ft_create_aperture(t_camera *cam)
{
	double	defocus_radius;
	t_vec3	viewport_top_left;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;

	if (ft_near_zero(cam->orient))
		cam->orient = ft_vec3_create(0, 0, -1);
	cam->lookat = ft_op(cam->pos, '+', cam->orient);
	w = ft_normalized(ft_op(cam->pos, '-', cam->lookat));
	u = ft_normalized(ft_cross(ft_vec3_create(0, 1, 0), w));
	v = ft_cross(w, u);
	cam->pxl_delta_u = ft_ops(ft_ops(u, '*', cam->viewp_w), '/', cam->render_width);
	cam->pxl_delta_v = ft_ops(ft_ops(v, '*', -cam->viewp_h), '/', cam->render_height);
	viewport_top_left = ft_def_viewp_top_lft(cam, u, v, w);
	cam->pxl_00 = ft_op(viewport_top_left, '+' , ft_ops(ft_op(cam->pxl_delta_u, '+', cam->pxl_delta_v), '/', 2));
	defocus_radius = cam->focus_dist * tan(ft_degr_to_rad(cam->defocus_angle / 2.0));
	cam->defocus_disk_u = ft_ops(u,'*', defocus_radius);
	cam->defocus_disk_v = ft_ops(v, '*', defocus_radius);
}

void	create_default_camera(t_camera *camera)
{
	if (camera->render_width == 0)
		camera->render_width = WIDTH;
	if (camera->render_height == 0)
		camera->render_height = (int)(WIDTH / RATIO) - (TOP_BAR + BOTTOM_BAR);
	camera->focal_lth = 2.0;
	if (camera->focus_dist == 0)
		camera->focus_dist = 1.0;
	camera->samples = SAMPLES_PER_PIXEL;
	camera->max_depth = MAX_DEPTH;
	camera->viewp_h = 2.0 * (tan(ft_degr_to_rad(camera->fov) / 2.0)) * camera->focus_dist;
	camera->viewp_w = camera->viewp_h * (double)camera->render_width / (double)camera->render_height;
	ft_create_aperture(camera);
	camera->clip.min = 0.00001;
	camera->clip.max = 16384.0;
	return (camera);
}

t_ray	ft_cam_get_ray(t_camera c, double u, double v)
{
	t_ray	ray;
	t_vec3	temp1;
	t_vec3	temp2;
	t_vec3	temp3;

	ray = (t_ray){0};
	temp1 = ft_op(c.lower_left_corner, '+', ft_ops(c.horizontal, '*', u));
	temp2 = ft_op(temp1, '+', ft_ops(c.vertical, '*', v));
	temp3 = ft_op(temp2, '-', c.origin);
	ray = (t_ray){c.origin, temp3};
	return (ray);
}

double	ft_rand_dbl(double min, double max)
{
	if(min != 0 && max != 0)
		return (min + (max - min) * rand() / (RAND_MAX + 1.0));
	return (rand() / (RAND_MAX + 1.0));
}

t_vec3 ft_rand_vec(double min, double max)
{
	t_vec3 vec;
	if (min != 0 && max != 0)
	{
		vec.x = ft_rand_dbl(min, max);
		vec.y = ft_rand_dbl(min, max);
		vec.z = ft_rand_dbl(min, max);
	}
	else
	{
		vec.x = ft_rand_dbl(0, 0);
		vec.y = ft_rand_dbl(0, 0);
		vec.z = ft_rand_dbl(0, 0);
	}
	return (vec);
}

t_vec3 ft_rand_usphere(void)
{
	t_vec3 p;

	while(1)
	{
		p = ft_rand_vec(-1., 1.);
		if(ft_dot(p, p)>=1.0)
			continue;
		return (p);
	}
}
t_vec3 ft_rand_uvec()
{
	return (ft_normalized(ft_rand_usphere()));
}

t_vec3 ft_rand_hemisph(t_vec3 normal)
{
	t_vec3 in_unit_sphere = ft_rand_usphere();
	if(ft_dot(in_unit_sphere, normal) > 0.0)
		return (in_unit_sphere);
	else
		return (ft_ops(in_unit_sphere, -1.0, MUL));
}

t_lambertian ft_create_lamb(t_color albedo)
{
	t_lambertian ret;

	ret = (t_lambertian){0};
	ret.type = LAMBERTIAN;
	ret.albedo = albedo;
	return (ret);
}

t_metal ft_create_metal(t_color albedo, double fuzz)
{
	t_metal ret;

	ret = (t_metal){0};
	ret.type = METAL;
	ret.albedo = albedo;
	if (fuzz < 1.0)
		ret.fuzz = fuzz;
	else
		ret.fuzz = 1.0;
	return (ret);
}

t_dielectric ft_create_dielectric (float ir)
{
  t_dielectric ret;
  
  ret = (t_dielectric){0, 0.};
  ret.type = DIELECTRIC;
  ret.ir = ir;
  return ret;
}

float ft_reflectance (float cos, float ir)
{
  float r0 = (1. - ir) / (1. + ir);
  r0 *= r0;
  return r0 + (1 - r0) * pow ((1 - cos), 5);
}

t_diffuse_light ft_create_diffuse_light(t_color emitted)
{
	t_diffuse_light ret;

	ret = (t_diffuse_light){0};
	ret.type = DIFFUSE_LIGHT;
	ret.emitted = emitted;
	return (ret);
}

int ft_lamb_scatter(t_lambertian lamb, t_hit_record *rec, t_color *attenuation, t_ray *scattered)
{
	t_vec3 scatter_direction;
	scatter_direction = ft_op(rec->normal, '+', ft_rand_usphere());
	if(ft_near_zero(scatter_direction))
		scatter_direction = rec->normal;
	*scattered = (t_ray){rec->p, scatter_direction};
	*attenuation = lamb.albedo;
	return (1);
}

int ft_metal_scatter(t_metal metal, t_ray ray_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered)
{
	t_vec3 reflected;
	
	reflected = ft_reflect(ft_normalized(ray_in.direction), rec->normal);
	*scattered = (t_ray){rec->p, reflected};
	*attenuation = metal.albedo;
	return (ft_dot(scattered->direction, rec->normal) > 0);
}

t_vec3 ft_refract(t_vec3 u, t_vec3 n, double etai_over_etat)
{
	double cos_theta = fmin (ft_dot(ft_ops(u, '*', -1.0), n), 1.0);
	t_vec3 cos_theta_n = ft_ops(n, '*', cos_theta);
	t_vec3 r_out_perp = ft_ops(ft_op(u, '+', cos_theta_n), '*', etai_over_etat);
	t_vec3 r_out_parallel = ft_ops(n, '*', 
					-sqrt(fabs((double) 1. - ft_dot(r_out_perp, r_out_perp))));
	return (ft_op(r_out_perp, '+', r_out_parallel));
	}

int ft_dieletric_scatter(t_dielectric dielectric, t_ray ray_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered)
{
	double	refraction_ratio;
	double	cos_theta;
	double	sin_theta;
	int		cannot_refract;
	t_vec3	unit_direction;
	t_vec3 direction;

	*attenuation = (t_color){1.0, 1.0, 1.0};
	if(rec->front_face != 0)
		refraction_ratio = (1.0) / dielectric.ir;
	else
		refraction_ratio = dielectric.ir;

	unit_direction = ft_normalized(ray_in.direction);
	cos_theta = fmin(ft_dot(ft_ops(unit_direction, '*', -1.0), rec->normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	cannot_refract = refraction_ratio * sin_theta > 1.0;
	direction = (t_vec3){0.0, 0.0, 0.0};
	if(cannot_refract || ft_reflectance(cos_theta, refraction_ratio) > ft_rand_dbl(0,0))
		direction = ft_reflect(unit_direction, rec->normal);
	else
		direction = ft_refract(unit_direction, rec->normal, refraction_ratio);
	*scattered = (t_ray){rec->p, direction};
	return (1);
}

int ft_material_scatter(t_material *material, t_ray ray_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered)
{
	if(material->type == LAMBERTIAN)
		return (ft_lamb_scatter(*(t_lambertian*) material, rec, attenuation, scattered));
	else if(material->type == METAL)
		return (ft_metal_scatter(*(t_metal*) material, ray_in, rec, attenuation, scattered));
	else if(material->type == DIELECTRIC)
		return (ft_dieletric_scatter(*(t_dielectric*) material, ray_in, rec, attenuation, scattered));
	return (0);
}

t_color ft_diffuse_emit(t_diffuse_light light)
{
	return (light.emitted);
}

t_color ft_material_emit(t_material *material)
{
	if(material->type == DIFFUSE_LIGHT)
		return (ft_diffuse_emit(*(t_diffuse_light*) material));
	return ((t_color){0.0,0.0,0.0});
}
*/