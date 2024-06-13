#include "minirt.h"

void	get_1_amb(t_scene *scene)
{
	scene->ambient.ratio = get_ratio(scene->split[1], A_RATIO, scene);
	scene->ambient.color = get_colour(scene->split[2], A_RGB, scene);
	scene->ambient.color = (t_color) {normalize_color(scene->ambient.color.x),
									normalize_color(scene->ambient.color.y), 
									normalize_color(scene->ambient.color.z), 3};
}

/****************CAMERA************/

void	get_2_cam(t_scene *scene)
{
	double		fov;
	
	fov = get_fov(scene->split[3], C_FOV, scene);
	scene->camera = ft_create_camera(WIDTH, WIDTH/RATIO, fov);
	scene->camera->point = get_coord(scene->split[1], C_COORD, scene);
	scene->camera->normalized = ft_normalize(get_normal(scene->split[2], C_NORM, scene));
	scene->camera->point = (t_point) {scene->camera->point.x, scene->camera->point.y, scene->camera->point.z, 1};
	scene->camera->normalized = (t_vec3) {scene->camera->normalized.x, 
							scene->camera->normalized.y, scene->camera->normalized.z, 0};
}

static	t_camera	*set_camera(t_camera *camera)
{
	t_matrix	transformation;
	t_vec3		aux;
	t_vec3		up;

	if (ft_double_compare(1, fabs(camera->normalized.y)))
		up = (t_vec3) {1, 0, 0, 0};
	else
	{
		aux = ft_cross((t_vec3){0, 1, 0, 0}, camera->normalized);
		up = ft_cross(camera->normalized, aux);
	}
	transformation = ft_view_transform_matrix(camera->point, camera->normalized, up);
	ft_set_camera_transform(camera, transformation);
	return (camera);
}

t_camera	*setup_camera(t_scene *scene)
{
	return (set_camera(scene->camera));
}

/**********LIGHT************/

void	get_3_light(t_scene *scene)
{
	scene->lights = malloc_ver(sizeof(t_light));
	scene->lights->position = (t_point)(get_coord(scene->split[1], L_COORD, scene));
	scene->lights->position = (t_point) {scene->lights->position.x, scene->lights->position.y, scene->lights->position.z, 1};
	scene->lights->brightness = get_ratio(scene->split[2], L_RATIO, scene);
	scene->lights->intensity = (t_color)get_colour(scene->split[3], L_RGB, scene);
	scene->lights->intensity = (t_color) {normalize_color(scene->lights->intensity.x), 
										normalize_color(scene->lights->intensity.y), 
										normalize_color(scene->lights->intensity.z), 3};
	scene->lights->intensity = ft_ops(scene->lights->intensity, '*', scene->lights->brightness);
}
