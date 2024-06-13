#include "minirt.h"
//#include "scene.h"

bool	ft_isdouble(char *str)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str) - 1)
	{
		if (!(ft_isdigit(str[i]) == true || str[i] == '-' || str[i] == '+'
				|| str[i] == '.'))
			return (false);
		i++;
	}
	return (true);
}

int	ft_isnormal(t_vec3 n)
{
	if (n.x >= -1.0 && n.x <= 1.0 && n.y >= -1.0 && n.y <= 1.0 && n.z >= -1.0
		&& n.z <= 1.0)
		return (1);
	return (0);
}



t_vec3	get_coord(char *str, char *code, t_scene *scene)
{
	t_vec3	coord;
	char	**split;

	split = ft_split(str, ',');
	if (ft_strlen_2(split) != 3 || !(ft_isdouble(split[0]) == 1
		&& ft_isdouble(split[1]) == 1 && ft_isdouble(split[2]) == 1))
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

t_vec3	get_normal(char *str, char *code, t_scene *scene)
{
	t_vec3	coord;

	coord = get_coord(str, code, scene);
	if (!ft_isnormal(coord))
		ft_msg_error(scene, code);
	return (coord);
}
