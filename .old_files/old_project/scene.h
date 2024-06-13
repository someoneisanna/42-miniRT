#ifndef SCENE_H
# define SCENE_H

# include "libft.h"
//# include "minirt.h"
# include "vectors.h"
# include <stdbool.h>
# include <stddef.h>
# include <math.h>

typedef struct s_image t_image;
typedef struct s_vec3 t_vec3;

typedef struct s_resol
{
	int		x;
	int		y;
} t_resol;

typedef struct s_amb
{
	double	ratio;
	int		color;
} t_amb;

typedef struct s_cam
{
	//t_image			img;
	t_vec3			point;
	t_vec3			normal;
	float			fov;
	t_vec3			hor;
	t_vec3			ver;
	t_vec3			llc;
	struct s_cam	*next;
	struct s_cam	*prev;
}	t_cam;

typedef struct	s_elem
{
	t_vec3			point;
	t_vec3			normal;
	t_vec3			*vertex;
	int				qtd_vertex;
	t_vec3			color;
	double			ratio;
	double			diam;
	double			height;
	struct s_elem	*next;
} t_elem;

typedef struct	s_scene
{
	char	*line;
	char	**split;
	int 	**color;
	t_resol	resol;
	t_amb	amb;
	t_cam	*cam;
	t_elem	*light;
	t_elem	*sp;
	t_elem	*pl;
	t_elem	*sq;
	t_elem	*cy;	
	t_elem	*tr;
	int		qtys[9];
} t_scene;

typedef void	(*t_arr_sc)(t_scene *, t_elem **);

void	open_file(char *file, t_scene *scene);


size_t	ft_strlen_2(char **s);
size_t	ft_strlen(const char *s);
void	lst_add_back_elem(t_elem **lst, t_elem *new, int *qty);
void	lst_add_back_cam(t_cam **lst, t_cam *new, int *qty);
char	**ft_split(char const *s, char c);
void	*malloc_ver(size_t size);
int		ft_atoi(const char *str);
void	ft_split_free(char **s);

void	ft_error(char *msg);
int		ft_strnrcmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*get_scene_elem*/
void	get_0_resol(t_scene *scene, t_elem **new);
void	get_1_amb(t_scene *scene, t_elem **new);
void	get_2_cam(t_scene *scene, t_elem **new);
void	get_cam_info(t_scene *scene, t_cam *cam);
void	get_3_light(t_scene *scene, t_elem **new);

/*get_scene_objs*/
void	get_4_sp(t_scene *scene, t_elem **new);
void	get_5_pl(t_scene *scene, t_elem **new);
void	get_6_sq(t_scene *scene, t_elem **new);
void	get_7_cy(t_scene *scene, t_elem **new);
void	get_8_tr(t_scene *scene, t_elem **new);

/*get_coord*/
t_vec3	get_normal(char *str, char *code);
t_vec3	get_coord(char *str, char *code);
int	ft_isnormal(t_vec3 n);
bool	ft_isdouble(char *str);

/*get_ratio*/
double	ft_atod(const char *str);
double	get_ratio(char *str, char *code);
double	get_float(char *str, char *code);
double	get_size(char *str, char *code);

/*get_color*/
int		get_color(char *str, char *code);
bool	ft_str_isint(char *str);
int		ft_isdigit(int i);
bool	ft_is_rgb(int n);

/*get_int*/
int	get_posint(char *str, char *code);
float	get_fov(char *str, char *code);

#endif