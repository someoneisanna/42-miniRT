#include "exercises.h"
/* 
void ft_multiple_lights(t_world *w)
{
	t_shapes *floor = ft_create_shape(PLANE);
	floor->material.color = ft_color(1, 1, 1);
	floor->material.specular = 0;
	ft_add_shapes(&w->objects, floor);

	t_shapes *s = ft_create_shape(CYLINDER);
	t_matrix transform = ft_multiply_matrix(ft_create_translation_matrix(-0.2, 1, 0), ft_create_rotation_matrix('y', -PI/4));
	ft_set_shape_transform(s, transform);
	s->cylinder->minimum = -1;
	s->cylinder->maximum = 1;
	s->material.color = ft_color(1, 1, 1);
	s->material.diffuse = 0.7;
	s->material.specular = 0.3;
	ft_add_shapes(&w->objects, s);

	t_shapes *s2 = ft_create_shape(CUBE);
	ft_set_shape_transform(s2, ft_multiply_matrix(ft_create_translation_matrix(1.5, 0.5, -0.5), ft_create_scaling_matrix(0.5, 0.5, 0.5)));
	s2->material.color = ft_color(1, 1, 1);
	s2->material.diffuse = 0.8;
	s2->material.specular = 0.3;
	ft_add_shapes(&w->objects, s2);

	t_shapes *s3 = ft_create_shape(CONE);
	transform = ft_create_translation_matrix(-1.7, 1, -1.2);
	ft_set_shape_transform(s3, transform);
	s3->cone->minimum = -1;
	s3->cone->maximum = 0;
	s3->cone->closed = true;
	s3->material.color = ft_color(1, 1, 1);
	s3->material.diffuse = 0.7;
	s3->material.specular = 0.3;
	ft_add_shapes(&w->objects, s3);

	t_light *l1 = ft_create_point_light(ft_point(-10, 10, -10), ft_color(1, 0, 0),1.);
	t_light *l2 = ft_create_point_light(ft_point(0, 10, -10), ft_color(0, 1, 0), 1.);
	t_light *l3 = ft_create_point_light(ft_point(10, 10, -10), ft_color(0, 0, 1), 1.);

	w->lights = ft_lstnew(l1);
	ft_lstadd_back(&w->lights, ft_lstnew(l2));
	ft_lstadd_back(&w->lights, ft_lstnew(l3));

	w->camera = ft_create_camera(WIDTH, WIDTH/RATIO, PI/3);
	w->zero = ft_create_camera(WIDTH, WIDTH/RATIO, PI/3);
	transform = ft_view_transform_matrix(ft_point(0, 1.5, -5), ft_point(0, 1, 0), ft_vector(0, 1, 0));
	ft_set_camera_transform(w->camera, transform);
	ft_set_camera_transform(w->zero, transform);
	
	w->canvas = ft_render(w->camera, w);
	ft_panel_window(&w->img, WIDTH, WIDTH/RATIO, w->canvas.pixels);
}
 */