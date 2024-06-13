#include "exercises.h"
/* 
void ft_print_sphere(t_world *treedee)
{
	t_ray	ray;
	double   wall_z = 10;
	double   wall_size = 7.0;
	t_intersections *inter;
	t_light *light;

	t_shapes *shape = ft_create_shape(SPHERE);
	shape->material = ft_create_material();
	shape->material.color = ft_color(1, 0.2, 1);
	light = ft_create_point_light(ft_point(-10, 10, -10), ft_color(1, 1, 1), 1);
	ray.origin = ft_point(0, 0, -5);
	int height = WIDTH/RATIO;
	treedee->canvas = ft_create_canvas(WIDTH, height); 
	double pixel_size = wall_size / WIDTH;
	double half = wall_size / 2;
	t_color color = ft_color(1, 0, 0);
	
	int i = -1;
	while(++i< WIDTH)
	{
		double world_y = half - pixel_size * i;
		int j = -1;
		while(++j < height)
		{
			double world_x = -half + pixel_size * j;
			t_point position = ft_point(world_x, world_y, wall_z);
			ray.direction = ft_op(position, '-', ray.origin);
			inter = NULL;
			ft_intersect(&inter, shape, ray);
			t_intersection *verify = ft_hit(inter);
			if(verify)
			{
				t_point point = ft_ray_position(ray, verify->t);
				t_vec3 normal = ft_normal_at(verify->object, point);
				t_vec3 eyev = ft_ops(ft_normalize(ray.direction), '*', -1);
				color = ft_lighting(shape->material, shape, light, point, eyev, normal, false);
				ft_write_pixel(treedee->canvas, j, i, color);
			}
		}
	}
	ft_panel_window(&treedee->img, WIDTH, height, treedee->canvas.pixels);
}
 */