/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:35:51 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/30 17:32:34 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_perror(t_world *w, char *msg)
{
	ft_putstr_fd("\033[1m\033[31mError \033[0m\n", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	else
		perror(NULL);
	get_next_line(3, 1);
	if (w && w->line)
		free(w->line);
	exit(1);
}

double	ft_atof(t_world *w, char *s)
{
	double	res;
	double	fra;
	int		sig;

	res = 0;
	fra = 1;
	sig = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '\0')
		ft_perror(w, "Double is not valid");
	if (*s == '-')
		sig = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
		res = res * 10 + *s++ - '0';
	if (*s == '.')
		s++;
	while (ft_isdigit(*s))
	{
		res = res * 10 + *s++ - '0';
		fra *= 10;
	}
	return (res / fra * sig);
}

double	ft_get_double(t_world *w, char **line, char d)
{
	int		i;
	int		dot;
	char	s[32];

	i = -1;
	dot = 0;
	if (**line == ',')
		(*line)++;
	while (**line == ' ')
		(*line)++;
	if (**line == '-' || **line == '+')
		s[++i] = *(*line)++;
	while (**line != d && **line != '\n' && **line)
	{
		if (**line == '.')
			dot++;
		if ((!ft_isdigit(**line) && **line != '.' && **line != ' ')
			|| dot > 1 || i > 30)
			ft_perror(w, "Double is not valid");
		else if (**line != ' ')
			s[++i] = **line;
		(*line)++;
	}
	s[++i] = '\0';
	return (ft_atof(w, s));
}

t_point	ft_get_tuple(t_world *world, char **line, double w)
{
	double	color;
	t_vec3	tuple;

	color = 1;
	if (w == 3)
		color = 255.0;
	tuple = (t_vec3){-42, -42, -42, -42};
	while (**line)
	{
		if (**line == ' ')
			(*line)++;
		else if (ft_isdigit(**line) || **line == '-' || **line == '+')
		{
			tuple.x = ft_get_double(world, line, ',') / color;
			tuple.y = ft_get_double(world, line, ',') / color;
			tuple.z = ft_get_double(world, line, ' ') / color;
			tuple.w = w;
			break ;
		}
		else
			ft_perror(world, "Tuple is not valid");
	}
	if (w == 3 && ft_in_range(tuple, 0, 1) == false)
		ft_perror(world, "Color is not in range");
	return (tuple);
}

bool	ft_in_range(t_vec3 v, double min, double max)
{
	if (v.x < min || v.x > max
		|| v.y < min || v.y > max
		|| v.z < min || v.z > max)
		return (false);
	return (true);
}
