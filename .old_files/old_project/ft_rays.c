#include "minirt.h"
#include "hittable.h"
#include "rays.h"
#include "scene.h"

/*
t_point	rayat(t_ray ray, double t)
{
	t_point	ret;

	ret = ft_op(ray.origin, '+', ft_ops(ray.direction, '*', t));
	return (ret);
}

int	ft_lstelem(t_elem *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

t_color	ft_ray_pixel(int u, int v, t_scene *scene)
{
	t_camera	cam;
	t_ray		ray;
	int			s;
	int			size;
	t_hittable	*world;
	t_material	*material;
	t_color		col;

	t_elem *temp;
	temp = scene->sp;
	double i, j;
	
	size = ft_lstelem(scene->sp) + 1;
	world = (t_hittable *)malloc(sizeof(t_hittable) * size);
	material = (t_material *)malloc(sizeof(t_material) * size);
	
	material[0] = (t_material)ft_create_diffuse_light((t_color){1., 1., 1.});
	world[0] = (t_hittable)ft_create_sphere((t_point){0., 140.0, -1.}, 100., (t_material*)&material[0]);
	s = 1;
	while(scene->sp)
	{
		if(scene->sp->diam > 20)
			material[s] = (t_material)ft_create_lamb((t_color)scene->sp->color);
		else
			material[s] = (t_material)ft_create_metal((t_color)scene->sp->color, 0.);
		world[s] = (t_hittable)ft_create_sphere(scene->sp->point, scene->sp->diam, (t_material*)&material[s]);
		scene->sp = scene->sp->next;
		s++;
	}
	col = (t_color){0., 0., 0.};
	cam = create_default_camera();
	s = -1;
	while (++s < SAMPLES_PER_PIXEL)
	{
		i = ((double)u + ft_rand_dbl(0., 2.)) / scene->resol.x;
		j = ((double)v + ft_rand_dbl(0., 2.)) / scene->resol.y;
		ray = ft_cam_get_ray(cam, i, j);
		col = ft_op(col, '+', ray_color(ray, world, size, MAX_DEPTH));
	}
	col = ft_ops(col, '*', 1.0 / SAMPLES_PER_PIXEL);
	scene->sp = temp;
	return (col);
}

t_color	ray_color(t_ray ray, t_hittable *world, int world_size, int depth)
{
	t_hit_record	hit_record;
	
	hit_record = (t_hit_record){0};
	if (depth <= 0)
		return ((t_color){0., 0., 0.});
	if (ft_hittable_hitlist(world, world_size, ray, 0.0000001, INFINITY, &hit_record))
	{
		t_color attenuation;
		t_ray scattered;
		t_color emitted = ft_material_emit(hit_record.material);
		if(!ft_material_scatter(hit_record.material, ray, &hit_record, &attenuation, &scattered))
		{
			return (emitted);
		}
		else 
			return (ft_op(emitted, '+', ft_op(attenuation, '*', ray_color(scattered, world, world_size, depth - 1))));
	}
	return (t_color){0., 0., 0.};
}

void	ft_set_face_normal(t_hit_record *hit_record, t_ray ray, t_vec3 outward_normal)
{
	double i;

	i = ft_dot(ray.direction, outward_normal);
	hit_record->front_face = 0;
	if (i < 0)
	{
		hit_record->front_face = 1;
		hit_record->normal = outward_normal;
	}
	else
		hit_record->normal = ft_ops(outward_normal, '*', -1.0);
}
*/