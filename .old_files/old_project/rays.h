#ifndef RAYS_H
# define RAYS_H

# include "vectors.h"
# include <stdbool.h>

typedef struct s_color
{
	long		r;
	long		g;
	long		b;
	int			samples;
}				t_color;

enum e_material_type
{
	LAMBERTIAN,
	METAL,
	DIELECTRIC,
	DIFFUSE_LIGHT
};

typedef struct s_ray
{
	t_point	origin;
	t_vec3	direction;
}			t_ray;

typedef struct s_dielectric
{
  int type;
  double ir;
} t_dielectric;

typedef struct s_clip
{
	double	min;
	double	max;
}			t_clip;

typedef struct s_camera
{
	double	focal_lth;
	double	fov;
	double	defocus_angle;
	double	focus_dist;
	double	viewp_h;
	double	viewp_w;
	bool	hide_hdr;
	int		render_width;
	int		render_height;
	int		max_depth;
	int		cam_samples;
	int		samples;
	t_vec3	pos;
	t_vec3	orient;
	t_vec3	lookat;
	t_vec3	pxl_delta_u;
	t_vec3	pxl_delta_v;
	t_vec3	pxl_00;
	t_vec3	defocus_disk_u;
	t_vec3	defocus_disk_v;
	t_color	background;
	t_clip	clip;
	bool	ambient_set;


}			t_camera;

typedef struct s_lambertian
{
	int		type;
	t_color	albedo;
}	t_lambertian;

typedef struct t_metal
{
	int		type;
	t_color	albedo;
	double	fuzz;
}	t_metal;
typedef struct s_diffuse_light
{
	int type;
	t_color	emitted;

}	t_diffuse_light;

typedef union s_material
{
	int				type;
	t_lambertian	lambertian;
	t_metal			metal;
	t_dielectric	dielectric;
	t_diffuse_light	diffuse_light;
}	t_material;




t_point		rayat(t_ray ray, double t);
double		ft_rand_dbl(double min, double max);
void	create_default_camera(t_camera *camera);
t_ray		ft_cam_get_ray(t_camera cam, double u, double v);
t_vec3		ft_rand_usphere(void);


t_vec3		ft_rand_uvec(void);


t_vec3 ft_rand_hemisph(t_vec3 normal);
// t_color	ray_color(t_ray ray, t_hittable *world, int world_size, int depth);
// t_color ft_material_emit(t_material *material, t_ray ray_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered)



#endif