#include "minirt.h"

t_matrix	ft_aux_rotation(t_shapes *shape)
{
	t_matrix	rotate_y;
	t_matrix	rotate_z;
	t_matrix	rotate;

	rotate = ft_create_matrix(4, 4, YES);
	if (shape->normal.x)
		rotate = ft_rotation_matrix('z', shape->normal.x * M_PI/2);
	if (shape->normal.y)
	{
		rotate_y = ft_rotation_matrix('y', shape->normal.y * M_PI/2);
		if (shape->normal.x)
			rotate = ft_multiply_matrix(rotate, rotate_y);
		else
			rotate = rotate_y;
	}
	if (shape->normal.z)
	{
		rotate_z = ft_rotation_matrix('x', shape->normal.z * M_PI/2);
		if (shape->normal.x || shape->normal.y)
			rotate = ft_multiply_matrix(rotate, rotate_z);
		else
			rotate = rotate_z;
	}
	return (rotate);
}
