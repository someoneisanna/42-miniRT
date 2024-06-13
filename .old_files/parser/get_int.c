#include "minirt.h"
//#include "scene.h"

bool	ft_str_isint(char *str)
{
	int		i;

	i = 0;
	while(ft_isspace(str[i]))
		i++;
	while (i < (int)ft_strlen(str) - 1)
	{
		if (ft_isdigit(str[i]) == 0 || str[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

int	get_int(char *str, char *code, t_scene *scene)
{
	if (ft_str_isint(str) == false)
	{
		ft_msg_error(scene, code);
		return (0);
	}
	//printf("str1: %s\n", str);
	return (ft_atoi(str));
}

int	get_posint(char *str, char *code, t_scene *scene)
{
	int		pos;

	pos = get_int(str, code, scene);
	if (!(pos > 0))
	{
		ft_msg_error(scene, code);
		return (0);
	}
	return (pos);
}

static double	deg2rad(double deg)
{
	return ((M_PI / 180) * deg);
}

double	get_fov(char *str, char *code, t_scene *scene)
{
	double	fov;

	fov = get_int(str, code, scene);
	if (!(fov >= 0 && fov <= 180))
	{
		ft_msg_error(scene, code);
		return (0);
	}
	fov = deg2rad(fov);
	return (fov);
}
