#include "exercises.h"

/*void	ft_reflection(t_world *w)
{
	t_matrix transform;

	t_shapes *floor = ft_create_shape(PLANE);
	ft_set_shape_transform(floor, ft_create_translation_matrix(0, -1, 0));
	floor->material.pattern = ft_create_pattern(CHECKERS, (t_color)BLACK, (t_color)WHITE);
	floor->material.specular = 0;
	ft_add_shapes(&w->objects, floor);

	t_shapes *middle = ft_create_shape(SPHERE);
	transform = ft_create_scaling_matrix(2, 2, 2);
	transform = ft_multiply_matrix(transform, ft_create_translation_matrix(-0.8, 0.5, 0));
	ft_set_shape_transform(middle, transform);
	middle->material.color = ft_color(0.9, 0.9, 0.9);
	middle->material.diffuse = 0.1;
	middle->material.specular = 5;
	middle->material.shininess = 1600;
	middle->material.reflective = 1;
	ft_add_shapes(&w->objects, middle);

	t_shapes *right = ft_create_shape(SPHERE);
	transform = ft_create_translation_matrix(1.5, 0, -0.5);
	ft_set_shape_transform(right, transform);
	right->material.color = ft_color(0.5, 1, 0.1);
	ft_add_shapes(&w->objects, right);

	t_light *l1 = ft_create_point_light(ft_point(0, 10, -10), ft_color(1, 1, 1), 1);
	t_light *l2 = ft_create_point_light(ft_point(10, 10, 10), ft_color(1, 0, 0), 1);
	w->lights = ft_lstnew(&l1);
	ft_lstadd_back(&w->lights, ft_lstnew(&l2));

	w->camera = ft_create_camera(WIDTH, WIDTH/RATIO, PI/3);
	ft_set_camera_transform(w->camera, ft_view_transform_matrix(ft_point(0, 1, -7), ft_point(0, 1, 0), ft_vector(0, 1, 0)));
	
	w->canvas = ft_render(w->camera, w);
	ft_panel_window(&w->img, WIDTH, WIDTH/RATIO, w->canvas.pixels);
}*/

void	ft_refraction(t_world *w)
{
	t_matrix transform;

	t_shapes *floor = ft_create_shape(PLANE);
	transform = ft_create_translation_matrix(0, -1, 0);
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('y', PI/4));
	ft_set_shape_transform(floor, transform);
	floor->material.pattern = ft_create_pattern(CHECKERS, ft_color(0, 0, 0), ft_color(1, 1, 1));
	floor->material.specular = 0;
	floor->material.reflective = 0.1;
	ft_add_shapes(&w->objects, floor);

	t_shapes *right_wall = ft_create_shape(PLANE);
	transform = ft_create_translation_matrix(2, 0, 0);
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('y', PI/4));
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('x', PI/2));
	ft_set_shape_transform(right_wall, transform);
	right_wall->material.pattern = ft_create_pattern(CHECKERS, ft_color(0, 0, 0), ft_color(1, 1, 1));
	ft_add_shapes(&w->objects, right_wall);

	t_shapes *left_wall = ft_create_shape(PLANE);
	transform = ft_create_translation_matrix(-2, 0, 0);
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('y', -PI/4));
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('x', PI/2));
	ft_set_shape_transform(left_wall, transform);
	left_wall->material.pattern = ft_create_pattern(CHECKERS, ft_color(0, 0, 0), ft_color(1, 1, 1));
	ft_add_shapes(&w->objects, left_wall);

	t_shapes *blue = ft_create_shape(SPHERE);
	transform = ft_create_translation_matrix(-3.5, 0, -3);
	ft_set_shape_transform(blue, transform);
	blue->material.color = ft_color(0, 0, 1);
	ft_add_shapes(&w->objects, blue);

	t_shapes *red = ft_create_shape(SPHERE);
	transform = ft_create_translation_matrix(-1, 0.5, -3);
	transform = ft_multiply_matrix(transform, ft_create_scaling_matrix(1.5, 1.5, 1.5));
	ft_set_shape_transform(red, transform);
	red->material.color = ft_color(1, 0, 0);
	ft_add_shapes(&w->objects, red);

	t_shapes *green = ft_create_shape(SPHERE);
	transform = ft_create_translation_matrix(1.3, 0, -3);
	transform = ft_multiply_matrix(transform, ft_create_scaling_matrix(0.9, 0.9, 0.9));
	ft_set_shape_transform(green, transform);
	green->material.color = ft_color(0, 1, 0);
	ft_add_shapes(&w->objects, green);

	t_shapes *glass = ft_create_shape(SPHERE);
	transform = ft_create_translation_matrix(0, 1.5, -10);
	transform = ft_multiply_matrix(transform, ft_create_scaling_matrix(2, 2, 2));
	ft_set_shape_transform(glass, transform);
	glass->material.color = ft_color(0, 0, 0);
	glass->material.transparency = 1;
	glass->material.refractive_index = 1.5;
	ft_add_shapes(&w->objects, glass);

	t_light *l = ft_create_point_light(ft_point(0, 10, -15), ft_color(1, 1, 1), 1);
	w->lights = ft_lstnew(l);
	
	w->camera = ft_create_camera(WIDTH, WIDTH/RATIO, PI/3);
	transform = ft_view_transform_matrix(ft_point(1, 1, -20), ft_point(0, 1, 0), ft_vector(0, 1, 0));
	ft_set_camera_transform(w->camera, transform);

	w->canvas = ft_render(w->camera, w);
	ft_panel_window(&w->img, WIDTH, WIDTH/RATIO, w->canvas.pixels);
}

/*void	ft_triangle(t_world *w)
{
	t_matrix transform;

	t_shapes *floor = ft_create_shape(PLANE);
	ft_set_shape_transform(floor, ft_create_translation_matrix(0, -1, 0));
	floor->material.pattern = ft_create_pattern(CHECKERS, (t_color)BLACK, (t_color)WHITE);
	floor->material.specular = 0;
	ft_add_shapes(&w->objects, floor);

	t_shapes *middle = ft_create_shape(TRIANGLE);
	transform = ft_create_scaling_matrix(2, 2, 2);
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('y', -PI/4));
	transform = ft_multiply_matrix(transform, ft_create_translation_matrix(0.5, 0, 0.3));

	ft_set_shape_transform(middle, transform);
	middle->material.color = ft_color(0.9, 0.9, 0.9);
	middle->material.diffuse = 0.1;
	middle->material.specular = 5;
	middle->material.shininess = 1600;
	middle->material.reflective = 1;
	ft_add_shapes(&w->objects, middle);

	t_shapes *right = ft_create_shape(SPHERE);
	transform = ft_create_translation_matrix(1.5, 0, -0);
	ft_set_shape_transform(right, transform);
	right->material.color = ft_color(0.5, 1, 0.1);
	ft_add_shapes(&w->objects, right);

	t_light *l1 = ft_create_point_light(ft_point(0, 10, -10), ft_color(1, 1, 1), 1);
	t_light *l2 = ft_create_point_light(ft_point(10, 10, 10), ft_color(1, 0, 0), 1);
	w->lights = ft_lstnew(&l1);
	ft_lstadd_back(&w->lights, ft_lstnew(&l2));

	w->camera = ft_create_camera(WIDTH, WIDTH/RATIO, PI/3);
	ft_set_camera_transform(w->camera, ft_view_transform_matrix(ft_point(0, 1, -7), ft_point(0, 1, 0), ft_vector(0, 1, 0)));
	
	w->canvas = ft_render(w->camera, w);
	ft_panel_window(&w->img, WIDTH, WIDTH/RATIO, w->canvas.pixels);
}*/
