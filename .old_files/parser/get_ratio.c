#include "minirt.h"
//#include "scene.h"

double	ft_atod(const char *str) // str = "255"
{
	double	int_p;
	double	dec_p;
	double	sign;
	int		i;

	int_p = 0.0;
	dec_p = 0.0;
	sign = 1.0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = - 1.0;
	while (ft_isdigit(*str))
		int_p = int_p * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (ft_isdigit(*str))
			dec_p += (pow(10, i--) * (*str++ - '0'));
	}
	return (sign * (int_p + dec_p)); // return = 255.0
}

double	get_double(char *str, char *code, t_scene *scene)
{
	if (ft_isdouble(str) == false)
	{
		ft_msg_error(scene, code);
		return (0);
	}
	return (ft_atod(str));
}

double	get_ratio(char *str, char *code, t_scene *scene)
{
	double	n;

	n = get_double(str, code, scene);
	if (!(n >= 0.0 && n <= 1.0))
	{
		ft_msg_error(scene, code);
		return (0);
	}
	return (n);
}

double	get_size(char *str, char *code, t_scene *scene)
{
	double	n;

	n = get_double(str, code, scene);
	if (!(n > 0.0))
	{
		ft_msg_error(scene, code);
		return (0);
	}
	return (n);
}

