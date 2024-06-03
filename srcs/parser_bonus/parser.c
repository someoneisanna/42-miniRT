/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:32:00 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/30 17:07:11 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_parser(char *filename, t_world *w)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	if (ft_strncmp(filename + ft_strlen(filename) - 3, ".rt", 3))
		ft_perror(w, "Invalid file extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_perror(w, NULL);
	line = get_next_line(fd, 0);
	while (line)
	{
		if (*line != '\n' && *line != '#' && *line != '\0')
			ft_read_line(line, w, &count);
		free(line);
		line = get_next_line(fd, 0);
	}
	if (count < 3)
		ft_perror(w, "Missing elements");
	close(fd);
}

void	ft_read_line(char *line, t_world *w, int *count)
{
	while (*line == ' ')
		line++;
	if (*line == 'R')
		ft_get_resolution(line, w);
	else if (*line == 'A')
		*count += ft_get_ambient(line, w);
	else if (*line == 'C')
		*count += ft_get_camera(line, w);
	else if (*line == 'L')
		*count += ft_get_light(line, w);
	else if (*line == 's' && *(line + 1) == 'p')
		ft_get_sphere(line, w);
	else if (*line == 'p' && *(line + 1) == 'l')
		ft_get_plane(line, w);
	else if (*line == 'c' && *(line + 1) == 'y')
		ft_get_cylinder(line, w);
	else if (*line == 'c' && *(line + 1) == 'o')
		ft_get_cone(line, w);
	else if (*line == 't' && *(line + 1) == 'r')
		ft_get_triangle(line, w);
	else if (*line == 'c' && *(line + 1) == 'b')
		ft_get_cube(line, w);
	else
		ft_perror(w, "Invalid identifier");
}
