#include "exercises.h"

void ft_print_circle(t_world *print)
{
	t_ray	ray;
	double   wall_z = 10;
	double   wall_size = 7.0;
	t_intersections *inter;

	ray.origin = ft_point(0, 0, -5);
	int height = WIDTH/RATIO;
	print->canvas = ft_create_canvas(WIDTH, height);
	double pixel_size = wall_size / WIDTH;
	double half = wall_size / 2;
	t_color color = ft_color(1, 0, 0);
	t_shapes *shape = ft_create_shape(SPHERE);
	
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
			if(ft_hit(inter))
				ft_write_pixel(print->canvas, j, i, color);
		}
	}
	ft_panel_window(&print->img, WIDTH, height, print->canvas.pixels);
}
