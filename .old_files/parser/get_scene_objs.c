#include "minirt.h"

void	ft_sphere_transform(t_shapes *new)
{
	t_matrix	transform;
	t_matrix	scaling;
	t_matrix	final;

	transform = ft_translation_matrix(
				new->sphere->center.x, 
				new->sphere->center.y, 
				new->sphere->center.z);
	scaling = ft_scaling_matrix(
				new->sphere->diameter, 
				new->sphere->diameter, 
				new->sphere->diameter);
	final = ft_multiply_matrix(transform, scaling);
	new->inverted = ft_invert_matrix(final);
	new->transform = transform;
}

void	get_4_sp(t_scene *scene)
{
	scene->new = ft_create_shape(SPHERE);
	scene->new->sphere->center = get_coord(scene->split[1], SP_COORD, scene);
	scene->new->sphere->center = (t_vec3) {scene->new->sphere->center.x, 
								scene->new->sphere->center.y, scene->new->sphere->center.z, 0};
	scene->new->sphere->diameter = get_size(scene->split[2], SP_DIAM, scene) / 2;
	scene->new->material.color = get_colour(scene->split[3], SP_RGB, scene);
	scene->new->material.color = (t_color) {normalize_color(scene->new->material.color.x), 
										normalize_color(scene->new->material.color.y), 
										normalize_color(scene->new->material.color.z), 3};
	ft_sphere_transform(scene->new);
}

void	ft_plane_transform(t_shapes *new)
{	
	t_matrix	rotate;
	t_matrix	final;

	new->transform = ft_translation_matrix(new->plane->point.x, 
					new->plane->point.y, new->plane->point.z);
	rotate = ft_aux_rotation(new);
	final = ft_multiply_matrix(new->transform, rotate);
	ft_set_shape_transform(new, final);
}

void	get_5_pl(t_scene *scene)
{
	scene->new = ft_create_shape(PLANE);
	scene->new->plane->point = get_coord(scene->split[1], PL_COORD, scene);
	scene->new->plane->point = (t_vec3) {scene->new->plane->point.x, 
					scene->new->plane->point.y, scene->new->plane->point.z, 0};
	scene->new->normal = get_normal(scene->split[2], PL_COORD, scene);
	scene->new->normal = (t_vec3) {scene->new->normal.x, 
					scene->new->normal.y, scene->new->normal.z, 0};
	scene->new->material.color = get_colour(scene->split[3], PL_RGB, scene);
	scene->new->material.color = (t_color) {normalize_color(scene->new->material.color.x), 
										normalize_color(scene->new->material.color.y), 
										normalize_color(scene->new->material.color.z), 3};
	ft_plane_transform(scene->new);
}

void	ft_cylinder_transform(t_shapes *new)
{	
	t_matrix	translat;
	t_matrix	scaling;
	t_matrix	rotate;
	t_matrix	final;

	translat = ft_translation_matrix(new->cylinder->center.x, 
					new->cylinder->center.y, new->cylinder->center.z);
	scaling = ft_scaling_matrix(new->cylinder->diameter, new->cylinder->diameter, new->cylinder->diameter);
	new->transform = ft_multiply_matrix(translat, scaling);
	rotate = ft_aux_rotation(new);
	final = ft_multiply_matrix(new->transform, rotate);
	ft_set_shape_transform(new, final);
}

void	get_6_cy(t_scene *scene)
{
	scene->new = ft_create_shape(CYLINDER);
	scene->new->cylinder->center = get_coord(scene->split[1], CY_COORD, scene);
	scene->new->cylinder->center = (t_vec3) {scene->new->cylinder->center.x, 
								scene->new->cylinder->center.y, scene->new->cylinder->center.z, 0};
	scene->new->normal = (get_normal(scene->split[2], CY_NORM, scene));
	scene->new->normal = (t_vec3) {scene->new->normal.x, 
								scene->new->normal.y, scene->new->normal.z, 0};
	scene->new->cylinder->diameter = get_size(scene->split[3], CY_DIAM, scene) / 2;
	scene->new->cylinder->height = get_size(scene->split[4], CY_HEIGHT, scene);
	scene->new->material.color = get_colour(scene->split[5], CY_RGB, scene);
	scene->new->material.color = (t_color) {normalize_color(scene->new->material.color.x), 
								normalize_color(scene->new->material.color.y), 
								normalize_color(scene->new->material.color.z), 3};
	scene->new->cylinder->minimum = -scene->new->cylinder->height / 2;
	scene->new->cylinder->maximum = scene->new->cylinder->height / 2;
	scene->new->cylinder->closed = true;
	ft_cylinder_transform(scene->new);
}

void	ft_cone_transform(t_shapes *new)
{	
	t_matrix	translat;
	t_matrix	scaling;
	t_matrix	rotate;
	t_matrix	final;

	translat = ft_translation_matrix(new->cone->center.x, 
					new->cone->center.y, new->cone->center.z);
	scaling = ft_scaling_matrix(new->cone->diameter, 1, new->cone->diameter);
	new->transform = ft_multiply_matrix(translat, scaling);
	rotate = ft_aux_rotation(new);
	final = ft_multiply_matrix(new->transform, rotate);
	ft_set_shape_transform(new, final);
}

void	get_7_co(t_scene *scene)
{
	scene->new = ft_create_shape(CONE);
	scene->new->cone->center = get_coord(scene->split[1], CO_COORD, scene);
	scene->new->cone->center = (t_vec3) {scene->new->cone->center.x, 
								scene->new->cone->center.y, scene->new->cone->center.z, 0};
	scene->new->normal = get_normal(scene->split[2], CO_NORM, scene);
	scene->new->normal = (t_vec3) {scene->new->normal.x, 
								scene->new->normal.y, scene->new->normal.z, 0};
	scene->new->cone->diameter = get_size(scene->split[3], CO_DIAM, scene) / 2;
	scene->new->cone->height = get_size(scene->split[4], CO_HEIGHT, scene);
	scene->new->material.color = get_colour(scene->split[5], CO_RGB, scene);
	scene->new->material.color = (t_color) {normalize_color(scene->new->material.color.x), 
								normalize_color(scene->new->material.color.y), 
								normalize_color(scene->new->material.color.z), 3};
	scene->new->cone->minimum = -scene->new->cone->height / 2;
	scene->new->cone->maximum = 0;
	scene->new->cone->closed = true;
	ft_cone_transform(scene->new);
}

void	ft_cube_transform(t_shapes *new)
{	
	t_matrix	translat;
	t_matrix	scaling;
	t_matrix	rotate;
	t_matrix	final;

	translat = ft_translation_matrix(new->cube->center.x, 
					new->cube->center.y, new->cube->center.z);
	scaling = ft_scaling_matrix(new->cube->side, new->cube->side, new->cube->side);	
	new->transform = ft_multiply_matrix(translat, scaling);
	rotate = ft_aux_rotation(new);
	final = ft_multiply_matrix(new->transform, rotate);
	ft_set_shape_transform(new, final);
}

void	get_8_cb(t_scene *scene)
{
	scene->new = ft_create_shape(CUBE);
	scene->new->cube->center = get_coord(scene->split[1], CB_COORD, scene);
	scene->new->cube->center = (t_vec3) {scene->new->cube->center.x, 
								scene->new->cube->center.y, scene->new->cube->center.z, 0};
	scene->new->normal = get_normal(scene->split[2], CB_NORM, scene);
	scene->new->normal = (t_vec3) {scene->new->normal.x, 
								scene->new->normal.y, scene->new->normal.z, 0};
	scene->new->cube->side = get_size(scene->split[3], CB_SIZE, scene);
	scene->new->material.color = get_colour(scene->split[4], CB_RGB, scene);
	scene->new->material.color = (t_color) {normalize_color(scene->new->material.color.x), 
								normalize_color(scene->new->material.color.y), 
								normalize_color(scene->new->material.color.z), 3};
	ft_cube_transform(scene->new);
}



void	get_9_tr(t_scene *scene)
{
	scene->new = ft_create_shape(TRIANGLE);
	scene->new->triangle->p1 = get_coord(scene->split[1], TR_P1, scene);
	scene->new->triangle->p1 = (t_vec3) {scene->new->triangle->p1.x, 
								scene->new->triangle->p1.y, scene->new->triangle->p1.z, 0};
	scene->new->triangle->p2 = get_coord(scene->split[2], TR_P2, scene);
	scene->new->triangle->p2 = (t_vec3) {scene->new->triangle->p2.x, 
								scene->new->triangle->p2.y, scene->new->triangle->p2.z, 0};
	scene->new->triangle->p3 = get_coord(scene->split[3], TR_P3, scene);
	scene->new->triangle->p3 = (t_vec3) {scene->new->triangle->p3.x, 
								scene->new->triangle->p3.y, scene->new->triangle->p3.z, 0};

	ft_set_triangle_pts(scene->new->triangle, scene->new->triangle->p1, 
							scene->new->triangle->p2, scene->new->triangle->p3);
	
	scene->new->material.color = get_colour(scene->split[4], TR_RGB, scene);
	scene->new->material.color = (t_color) {normalize_color(scene->new->material.color.x), 
								normalize_color(scene->new->material.color.y), 
								normalize_color(scene->new->material.color.z), 3};
	ft_set_shape_transform(scene->new, ft_scaling_matrix(0.9, 0.9, 0.9));
}
