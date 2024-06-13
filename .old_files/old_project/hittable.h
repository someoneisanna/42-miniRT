#ifndef HITTABLE_H
# define HITTABLE_H

# include "rays.h"
# include "vectors.h"

enum e_hittable_type
{
	SPHERE,
	CYLINDER,
	PLANE
};

typedef struct s_hit_record
{
	t_point p;
	t_vec3 normal;
	double t;
	int front_face;
	t_material *material;
}				t_hit_record;

typedef struct s_sphere
{	
	int type;
	t_point center;
	double radius;
	t_material *material;
}				t_sphere;

typedef union s_hittable
{
	int type;
	t_sphere	sphere;
}				t_hittable;

typedef struct s_hit_list
{
  t_hittable *data;
  int size;
  int max_size;
} t_hit_list;


int ft_touch_sphere(t_sphere sphere, t_ray ray, double t_min, double t_max, t_hit_record *hit_record);
void ft_set_face_normal(t_hit_record *hit_record, t_ray ray, t_vec3 outward_normal);
int ft_hittable_hit(t_hittable hit, t_ray ray,double t_min, double t_max,t_hit_record *hit_record);
int ft_hittable_hitlist(t_hittable *hittable, int hit_list_size, t_ray ray, double t_min, double t_max, t_hit_record *hit_record);
t_sphere ft_create_sphere (t_point center, float radius, t_material *material);
t_color	ray_color(t_ray _ray, t_hittable *world, int world_size, int depth);
int ft_lamb_scatter(t_lambertian lamb, t_hit_record *rec, t_color *attenuation, t_ray *scattered);
int ft_metal_scatter(t_metal metal, t_ray ray_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered);
int ft_material_scatter(t_material *material, t_ray ray_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered);
t_lambertian ft_create_lamb(t_color albedo);
t_metal ft_create_metal(t_color albedo, double fuzz);
t_diffuse_light ft_create_diffuse_light(t_color emitted);
t_color ft_material_emit(t_material *material);
t_color ft_diffuse_emit(t_diffuse_light light);
t_dielectric ft_create_dielectric(float ir);
void ft_init_hittable_list (t_hit_list *list,int max_size);
int ft_hit_list_add(t_hit_list * list, t_hittable * hittable);
void ft_destroy_hittable_list (t_hit_list * list);
int ft_hit_list_hit (t_hit_list *hit_list, t_ray ray, double t_min, double t_max, t_hit_record *rec);


#endif