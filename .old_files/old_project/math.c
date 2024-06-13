// https://github.com/tjensen42/42-miniRT/tree/main/src/math

#include "minirt.h"
#include "vectors.h"
#include <math.h>

t_vec3	ft_vec3_create(double e0, double e1, double e2)
{
	t_vec3 v;

	v.x = e0;
	v.y = e1;
	v.z = e2;
	return (v);
}

double	ft_vec3normsquared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3	ft_normalized(t_vec3 vec)
{
	double norm;

	norm = sqrt(ft_dot(vec, vec));
	return ((t_vec3){vec.x / norm, vec.y / norm, vec.z / norm});
}

t_vec3	ft_op(t_vec3 vec1, char op, t_vec3 vec2)
{
	if (op == '+')
		return ((t_vec3){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
	else if (op == '-')
		return ((t_vec3){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
	else if (op == '*')
		return ((t_vec3){vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z});
	else
		return ((t_vec3){0, 0, 0});
}

t_vec3	ft_ops(t_vec3 vec, char op, double a)
{
	if (op == '+')
		return ((t_vec3){vec.x + a, vec.y + a, vec.z + a});
	else if (op == '-')
		return ((t_vec3){vec.x - a, vec.y - a, vec.z - a});
	else if (op == '*')
		return ((t_vec3){vec.x * a, vec.y * a, vec.z * a});
	else if (op == '/')
	{	
		if (a == 0)
			a = 1e-9;
		return ((t_vec3){vec.x / a, vec.y / a, vec.z / a});
	}
	else
		return ((t_vec3){0, 0, 0});
}

double	ft_dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	ft_cross(t_vec3 u, t_vec3 v)
{
	t_vec3 w;

	w.x = u.y * v.z - u.z * v.y;
	w.y = u.z * v.x - u.x * v.z;
	w.z = u.x * v.y - u.y * v.x;
	return (w);
}

int	ft_near_zero(t_vec3 v)
{
	double s;
	
	s = 1e-8;
	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}

t_vec3	ft_reflect(t_vec3 v, t_vec3 n)
{
	return (ft_op(v, '-', ft_ops(n, '*', 2 * ft_dot(v, n))));
}

double	ft_degr_to_rad(double angle)
{
	return (angle * PI / 180.0);
}

t_vec3	ft_rgb_to_double(int color)
{
	t_vec3	col;

	col.x = (double)((color >> 16) & 0xFF) / 255.0;
	col.y = (double)((color >> 8) & 0xFF) / 255.0;
	col.z = (double)(color & 0xFF) / 255.0;
	return (col);
}

/*
void	ft_draw_rect(t_vec3 top_left, t_vec3 bottom_right, t_color clr, t_img *img)
{
	int	x;
	int	y;

	x = top_left.x - 1;
	while (++x < bottom_right.x + top_left.x)
	{
		y = top_left.y - 1;
		while (++y < bottom_right.y + top_left.y)
			put_pxl(x, y, clr, img);
	}
}
*/