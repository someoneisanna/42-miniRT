#include "hittable.h"
#include "minirt.h"
#include "rays.h"

/*
int	ft_hittable_hit(t_hittable hit, t_ray ray, double t_min, double t_max,
		t_hit_record *hit_record)
{
	if (hit.type == SPHERE)
		return (ft_touch_sphere(*(t_sphere *)&hit, ray, t_min, t_max, hit_record));
	return (0);
}

int	ft_hittable_hitlist(t_hittable *hittable, int hit_list_size, t_ray ray,
		double t_min, double t_max, t_hit_record *hit_record)
{
	int				hit_anything;
	double			closest_so_far;
	t_hit_record	temp_rec;
	int				i;

	hit_anything = 0;
	closest_so_far = t_max;
	i = -1;
	while (++i < hit_list_size)
	{
		if (ft_hittable_hit(hittable[i], ray, t_min, closest_so_far, &temp_rec))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*hit_record = temp_rec;
		}
	}
	return (hit_anything);
}

void	ft_init_hittable_list(t_hit_list *list, int max_size)
{
	list->size = 0;
	list->max_size = max_size;
	list->data = malloc(max_size * sizeof(t_hittable));
}

int	ft_hit_list_add(t_hit_list *list, t_hittable *hittable)
{
	if (list->size == list->max_size)
		return (0);
	list->data[list->size] = *hittable;
	list->size++;
	return (1);
}

void	ft_destroy_hittable_list(t_hit_list *list)
{
	free(list->data);
}

int	ft_hit_list_hit(t_hit_list *hit_list, t_ray ray, double t_min, double t_max,
		t_hit_record *rec)
{
	int				hit_anything;
	float			closest_so_far;
	t_hit_record	temp_rec;
	t_hittable		current;

	hit_anything = 0;
	closest_so_far = t_max;
	for (int i = 0; i < hit_list->size; i++)
	{
		current = hit_list->data[i];
		if (ft_hittable_hit(current, ray, t_min, closest_so_far, &temp_rec))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}
	return (hit_anything);
}
*/