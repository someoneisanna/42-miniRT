#include "exercises.h"

//void ft_chapter_10(t_world *w)
//{
	/* t_shapes *floor = ft_create_shape(PLANE);
	t_matrix transform = ft_create_translation_matrix(0, -0.2, 0);
	ft_set_shape_transform(floor, transform);
	floor->material.pattern = ft_create_pattern(GRADIENT, ft_color(0.2, 1, 1), ft_color(1, 1, 0.5));
	ft_add_shapes(&w->objects, floor);

	t_shapes *right_wall = ft_create_shape(PLANE);
	transform = ft_create_translation_matrix(2, 0, 0);
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('y', PI/4));
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('x', PI/2));
	ft_set_shape_transform(right_wall, transform);
	right_wall->material.pattern = ft_create_pattern(RING, ft_color(0.2, 1, 1), ft_color(1, 1, 0.5));
	right_wall->material.specular = 0;
	ft_add_shapes(&w->objects, right_wall);

	t_shapes *left_wall = ft_create_shape(PLANE);
	transform = ft_create_translation_matrix(-2, 0, 0);
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('y', -PI/4));
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('x', PI/2));
	ft_set_shape_transform(left_wall, transform);
	left_wall->material.pattern = ft_create_pattern(STRIPES, ft_color(0.2, 1, 1), ft_color(1, 1, 0.5));
	left_wall->material.specular = 0;
	ft_add_shapes(&w->objects, left_wall);

	t_shapes *middle = ft_create_shape(CYLINDER);
	transform = ft_create_translation_matrix(-0.2, 1.2, 0);
	// transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('z', PI/3));
	// transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('x', PI/4));
	ft_set_shape_transform(middle, transform);
	middle->cylinder->closed = true;
	middle->cylinder->minimum = -1;
	middle->cylinder->maximum = 1;
	middle->material.pattern = ft_create_pattern(NONE, ft_color(0.2, 0.1, 0.1), ft_color(0.9, 0.7, 0.5));
	// middle->material.pattern = ft_create_xpm_pattern(XPM, XPM_FILE);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.3;
	ft_add_shapes(&w->objects, middle);

	t_shapes *right = ft_create_shape(SPHERE);
	transform = ft_create_translation_matrix(1.5, 0.5, -0.5);
	// transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('y', PI/2));
	transform = ft_multiply_matrix(transform, ft_create_scaling_matrix(0.5, 0.5, 0.5));
	ft_set_shape_transform(right, transform);
	// right->material.pattern = ft_create_pattern(RING, ft_color(1, 0.7, 0.5), ft_color(1, 1, 0.3));
	right->material.pattern = ft_create_xpm_pattern(XPM, XPM_FILE);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;
	ft_add_shapes(&w->objects, right); */

/* 	t_shapes *left = ft_create_shape(SPHERE);
	t_matrix transform = ft_create_translation_matrix(-1.5, 0.33, -0.75);
	transform = ft_multiply_matrix(transform, ft_create_scaling_matrix(0.33, 0.33, 0.33));
	ft_set_shape_transform(left, transform);
	left->material.pattern = ft_create_pattern(RING, ft_color(0.3, 0.7, 1), ft_color(1, 0.9, 0.2));
	// left->material.pattern = ft_create_xpm_pattern(XPM, XPM_FILE3);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;
	ft_add_shapes(&w->objects, left);

	t_light *l = ft_create_point_light(ft_point(-5, 5, -10), ft_color(1, 1, 1), 1);
	w->lights = ft_lstnew(l);
	w->camera = ft_create_camera(WIDTH, WIDTH/RATIO, PI/3);
	transform = ft_view_transform_matrix(ft_point(0, 1.5, -5), ft_point(0, 1, 0), ft_vector(0, 1, 0));
	ft_set_camera_transform(w->camera, transform);

	w->canvas = ft_render(w->camera, w);
	ft_panel_window(&w->img, WIDTH, WIDTH/RATIO, w->canvas.pixels); */
//}

void ft_snowman(t_world *w)
{
	t_matrix transform;
	t_shapes *floor = ft_create_shape(PLANE);
	transform = ft_create_translation_matrix(0, -1, 0);
	ft_set_shape_transform(floor, transform);
	floor->material.color = ft_color(1, 1, 1);
	floor->material.specular = 0;
	ft_add_shapes(&w->objects, floor);

	t_shapes *eye1 = ft_create_shape(SPHERE);
	transform = ft_multiply_matrix(ft_create_translation_matrix(-0.2, 1.6, -0.68), ft_create_scaling_matrix(0.05, 0.05, 0.05));
	ft_set_shape_transform(eye1, transform);
	eye1->material.color = ft_color(0, 0, 0);
	eye1->material.diffuse = 0.8;
	eye1->material.specular = 0.3;
	ft_add_shapes(&w->objects, eye1);

	t_shapes *eye2 = ft_create_shape(SPHERE);
	transform = ft_multiply_matrix(ft_create_translation_matrix(0.2, 1.6, -0.68), ft_create_scaling_matrix(0.05, 0.05, 0.05));
	ft_set_shape_transform(eye2, transform);
	eye2->material.color = ft_color(0, 0, 0);
	eye2->material.diffuse = 0.8;
	eye2->material.specular = 0.3;
	ft_add_shapes(&w->objects, eye2);

	t_shapes *s2 = ft_create_shape(SPHERE);
	transform =ft_multiply_matrix(ft_create_translation_matrix(0, 1.5, 0), ft_create_scaling_matrix(0.7, 0.7, 0.7));
	ft_set_shape_transform(s2, transform);
	s2->material.color = ft_color(1, 1, 1);
	s2->material.diffuse = 0.8;
	s2->material.specular = 0.3;
	ft_add_shapes(&w->objects, s2);

	t_shapes *s3 = ft_create_shape(SPHERE);
	s3->material.color = ft_color(1, 1, 1);
	s3->material.diffuse = 0.8;
	s3->material.specular = 0.3;
	ft_add_shapes(&w->objects, s3);

	t_shapes *nose = ft_create_shape(CONE);
	transform = ft_create_translation_matrix(0, 1.35, -1);
	transform = ft_multiply_matrix(transform, ft_create_scaling_matrix(0.1, 0.1, 0.2));
	transform = ft_multiply_matrix(transform, ft_create_rotation_matrix('x', -PI/2));
	ft_set_shape_transform(nose, transform);
	nose->cone->minimum = -1;
	nose->cone->maximum = 0;
	nose->cone->closed = true;
	nose->material.color = ft_color(0.7, 0, 0);
	nose->material.diffuse = 0.8;
	nose->material.specular = 0.3;
	ft_add_shapes(&w->objects, nose);

	t_shapes *hat = ft_create_shape(CYLINDER);
	transform = ft_create_translation_matrix(0, 2.5, 0.2);
	transform = ft_multiply_matrix(transform, ft_create_scaling_matrix(0.7, 0.7, 0.7));
	ft_set_shape_transform(hat, transform);
	hat->cylinder->minimum = -0.8;
	hat->cylinder->maximum = 0;
	hat->cylinder->closed = true;
	hat->material.color = ft_color(0, 1, 0);
	hat->material.diffuse = 0.8;
	hat->material.specular = 0.3;
	ft_add_shapes(&w->objects, hat);

	t_shapes *hat2 = ft_create_shape(SPHERE);
	transform = ft_create_translation_matrix(0, 2, 0);
	transform = ft_multiply_matrix(transform, ft_create_scaling_matrix(1, 0.1, 1));
	ft_set_shape_transform(hat2, transform);
	hat2->material.color = ft_color(0, 1, 0);
	hat2->material.diffuse = 0.8;
	hat2->material.specular = 0.3;
	ft_add_shapes(&w->objects, hat2);

	t_light *l1 = ft_create_point_light(ft_point(-10, 10, -10), ft_color(1, 0, 0), 1.0);
	t_light *l2 = ft_create_point_light(ft_point(0.1, 10, -10), ft_color(0, 1, 0), 1.0);
	t_light *l3 = ft_create_point_light(ft_point(10, 10, -10), ft_color(0, 0, 1), 1.0);

	w->lights = ft_lstnew(&l1);
	ft_lstadd_back(&w->lights, ft_lstnew(&l2));
	ft_lstadd_back(&w->lights, ft_lstnew(&l3));

	w->camera = ft_create_camera(WIDTH, WIDTH/RATIO, PI/3);
	transform = ft_view_transform_matrix(ft_point(0, 1.5, -5), ft_point(0, 1, 0), ft_vector(0, 1, 0));
	ft_set_camera_transform(w->camera, transform);
	
	w->canvas = ft_render(w->camera, w);
	ft_panel_window(&w->img, WIDTH, WIDTH/RATIO, w->canvas.pixels);
} 
