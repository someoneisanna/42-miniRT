/* #include "exercises.h"

void	ft_spereres(t_shapes **s1, t_shapes **s2, t_shapes **s3)
{
	(*s1) = ft_create_shape(SPHERE);
	ft_set_shape_transform((*s1), ft_create_translation_matrix(-1, 1, 0.5));
	(*s1)->material = ft_create_material();
	(*s1)->material.color = ft_color(0.1, 1, 0.5);
	(*s1)->material.diffuse = 0.7;
	(*s1)->material.specular = 0.3;
	
	(*s3) = ft_create_shape(SPHERE);
	t_matrix transform = ft_multiply_matrix(ft_create_translation_matrix(1.5, 0.5, -0.5), ft_create_scaling_matrix(0.5, 0.5, 0.5));
	ft_set_shape_transform((*s3), transform);
	(*s3)->material = ft_create_material();
	(*s3)->material.color = ft_color(0.5,1.0 ,0.1);
	(*s3)->material.diffuse = 0.7;
	(*s3)->material.specular = 0.3;

	(*s2) = ft_create_shape(SPHERE);
	transform = ft_multiply_matrix(ft_create_translation_matrix(-1.5, 0.33, -0.75), 
											ft_create_scaling_matrix(0.33, 0.33, 0.33));
	ft_set_shape_transform((*s2), transform);
	(*s2)->material.color = ft_color(1, 0.34, 0.41);
	(*s2)->material.diffuse = 0.7;
	(*s2)->material.specular = 0.3;
}

void	ft_cube(t_shapes **floor, t_shapes **l_wall, t_shapes **r_wall)
{
	(*floor) = ft_create_shape(SPHERE);
	t_matrix transform = ft_create_scaling_matrix(10,0.01,10);
	ft_set_shape_transform((*floor), transform);
	(*floor)->material = ft_create_material();
	(*floor)->material.color = ft_color(1,.9,.9);
	(*floor)->material.specular = 0;

	(*l_wall) = ft_create_shape(SPHERE);
	transform = ft_multiply_matrix(ft_create_translation_matrix(0,0,5),
						ft_multiply_matrix(ft_create_rotation_matrix('y',-PI/4),
						ft_multiply_matrix(ft_create_rotation_matrix('x', PI/2),
						ft_create_scaling_matrix(10,0.01,10))));
	ft_set_shape_transform((*l_wall), transform);
	(*l_wall)->material = (*floor)->material;

	(*r_wall) = ft_create_shape(SPHERE);
	transform = ft_multiply_matrix(ft_create_translation_matrix(0,0,5),
						ft_multiply_matrix(ft_create_rotation_matrix('y', PI/4),
						ft_multiply_matrix(ft_create_rotation_matrix('x', PI/2),
						ft_create_scaling_matrix(10,0.01,10))));
	ft_set_shape_transform((*r_wall), transform);
	(*r_wall)->material = (*floor)->material;
}

void	ft_print_room(t_world *room)
{
	t_shapes		*sprere_but_bigger;
	t_shapes		*sprere_but_left;
	t_shapes		*sprere_but_not_left;
	// t_shapes		*floor;
	// t_shapes		*l_wall;
	// t_shapes		*r_wall;
	int				height;

	height = WIDTH / 2;
	// ft_cube(&floor, &l_wall, &r_wall);
	ft_spereres(&sprere_but_bigger, &sprere_but_left, &sprere_but_not_left);
	t_light *l = ft_create_point_light(ft_point(-10, 10, -10), ft_color(1, 1, 1), 1);
	room->lights = ft_lstnew(l);
	room->camera = ft_create_camera(WIDTH, height, PI / 3);
	t_matrix transform = ft_view_transform_matrix(ft_point(0, 1.5, -5), 
							ft_point(0, 1, 0), 
							ft_vector(0, 1, 0)); 
	ft_set_camera_transform(room->camera, transform);
	ft_add_shapes(&room->objects, sprere_but_bigger);
	// ft_add_shapes(&room->objects, sprere_but_left);
	// ft_add_shapes(&room->objects, sprere_but_not_left);
	// ft_add_shapes(&room->objects, floor);
	// ft_add_shapes(&room->objects, l_wall);
	// ft_add_shapes(&room->objects, r_wall);
	// while(room->objects)
	// {
	// 	ft_print_sphere(room, room->objects->content);
	// 	room->objects = room->objects->next;
	// }
	room->canvas = ft_render(room->camera, room);
	ft_panel_window(&room->img, WIDTH, height, room->canvas.pixels);
} */
