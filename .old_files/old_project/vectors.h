#ifndef VECTORS_H
# define VECTORS_H

# include <stdint.h>

# define X 0
# define Y 1
# define Z 2

# define R 0
# define G 1
# define B 2

# define MINUS 0
# define SUM 1
# define MUL 2
# define DIV 3

typedef struct s_vec3
{
			double	x;
			double	y;
			double	z;
}	t_vec3;

typedef t_vec3	t_point;

t_vec3	ft_vec3_create(double e0, double e1, double e2);
t_vec3	ft_op(t_vec3 u, char op, t_vec3 v);
t_vec3	ft_ops(t_vec3 vec, char op, double a);
double	ft_length(t_vec3 u);
double	ft_dot(t_vec3 u, t_vec3 v);
t_vec3	ft_cross(t_vec3 u, t_vec3 v);
t_vec3	ft_normalized(t_vec3 u);
void print_vec3(t_vec3 vec);
int		ft_int_to_rgb(t_vec3 color);
int ft_near_zero(t_vec3 v);
double ft_degr_to_rad(double degrees);
t_vec3 ft_reflect(t_vec3 v, t_vec3 n);
t_vec3	ft_rgb_to_double(int color);
t_vec3	ft_rgb_to_double(int color);

#endif
