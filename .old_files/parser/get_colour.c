#include "minirt.h"
//#include "scene.h"

bool	ft_is_rgb(int n)
{
	if (n >= 0 && n <= 256)
		return (true);
	return (false);
}

double	normalize_color(double color)
{
	return (color / 255.0);
}

t_vec3	get_colour(char *str, char *code, t_scene *scene)
{
	t_vec3	coord;
	char	**split;

	split = ft_split(str, ',');
	if (ft_strlen_2(split) != 3 || !(ft_str_isint(split[0]) == 1
		&& ft_str_isint(split[1]) == 1 && ft_str_isint(split[2]) == 1))
			ft_msg_error(scene, code);
	if (!split[0] || !split[1] || !split[2])
	{
		ft_msg_error(scene, code);
		coord.x = 0;
		coord.y = 0;
		coord.z = 0;
	}
	else
	{
		coord.x = ft_atod(split[0]);
		coord.y = ft_atod(split[1]);
		coord.z = ft_atod(split[2]);
	}
	ft_split_free(split);
	return (coord);
}