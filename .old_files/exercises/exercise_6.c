#include "exercises.h"
/* 
void ft_chapter_9(t_world *w)
{
	t_light *l = ft_create_point_light(ft_point(-10, 5, -10), ft_color(1, 1, 1), 1);
	w->lights = ft_lstnew(l);
	
	w->camera = ft_create_camera(WIDTH, WIDTH/RATIO, PI/3);
	t_matrix transform = ft_view_transform_matrix(ft_point(0, 1.5, -5), ft_point(0, 1, 0), ft_vector(0, 1, 0));
	ft_set_camera_transform(w->camera, transform);
	
	t_shapes *s = ft_create_shape(CYLINDER);
	s->material.color = ft_color(0.03, 0.72, 0.70);
	s->cylinder->minimum = -0.9;
	s->cylinder->maximum = 1;
	s->cylinder->closed = YES;
	transform = ft_create_scaling_matrix(0.5, 1, 0.5);
	ft_set_shape_transform(s, transform);
	ft_add_shapes(&w->objects, s);

	t_shapes *s2 = ft_create_shape(SPHERE);
	s2->material.color = ft_color(0.7, 0.3, 0.5);
	transform = ft_create_scaling_matrix(0.5, 0.5, 0.5);
	transform = ft_multiply_matrix(transform, ft_create_translation_matrix(-2, 0.7, -0.5));
	ft_set_shape_transform(s2, transform);
	ft_add_shapes(&w->objects, s2);

	t_shapes *s3 = ft_create_shape(SPHERE);
	s3->material.color = ft_color(0.1, 0.7, 0.5);
	transform = ft_create_scaling_matrix(2, 0.5, 0.5);
	transform = ft_multiply_matrix(transform, ft_create_translation_matrix(0, 5, -0.5));
	ft_set_shape_transform(s3, transform);
	ft_add_shapes(&w->objects, s3);
	
	t_shapes *floor = ft_create_shape(PLANE);
	transform = ft_create_translation_matrix(0, -0.2, 0);
	ft_set_shape_transform(floor, transform);
	floor->material.color = ft_color(1, 0.9, 0.9);
	floor->material.specular = 0;
	ft_add_shapes(&w->objects, floor);

	t_shapes *left_wall = ft_create_shape(PLANE);
	transform = ft_create_translation_matrix(2, 0, 0);
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('y', PI/4));
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('x', PI/2));
	ft_set_shape_transform(left_wall, transform);
	left_wall->material.color = ft_color(0.9, 0.7, 0.9);
	left_wall->material.specular = 0;
	ft_add_shapes(&w->objects, left_wall);

	t_shapes *right_wall = ft_create_shape(PLANE);
	transform = ft_create_translation_matrix(-2, 0, 0);
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('y', -PI/4));
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('x', PI/2));
	ft_set_shape_transform(right_wall, transform);
	right_wall->material.color = ft_color(0.9, 0.9, 0.3);
	right_wall->material.specular = 0;
	ft_add_shapes(&w->objects, right_wall);

	w->canvas = ft_render(w->camera, w);
	ft_panel_window(&w->img, WIDTH, WIDTH/RATIO, w->canvas.pixels);
}
 */