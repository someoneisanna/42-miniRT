/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:32:13 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/30 17:19:37 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Parses the xpm file and loads it into the canvas.
void	ft_load_xpm_to_matrix(t_canvas *scene, char *xpm_file)
{
	t_image	img_ptr;
	int		x;
	int		y;
	void	*mlx_ptr;
	int		*color;

	mlx_ptr = mlx_init();
	img_ptr.img = mlx_xpm_file_to_image(mlx_ptr, xpm_file, &scene->width,
			&scene->height);
	if (!img_ptr.img)
		printf("Error reading xpm file\n");
	color = (int *)mlx_get_data_addr(img_ptr.img, &img_ptr.bpp,
			&img_ptr.line_length, &img_ptr.endian);
	y = -1;
	while (++y < scene->height)
	{
		x = -1;
		while (++x < scene->width)
			scene->pixels[y][x] = ft_rgb_to_int(color[y * scene->width + x]);
	}
	mlx_destroy_image(mlx_ptr, img_ptr.img);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}

// Reads the xpm file and returns the canvas.
t_canvas	ft_read_xpm(char *xpm_file)
{
	int			fd;
	int			height;
	int			width;
	char		*line;
	t_canvas	texture;

	fd = open(xpm_file, O_RDONLY);
	if (fd < 0)
		ft_perror(NULL, "Error opening xpm file\n");
	while (1)
	{
		line = get_next_line(fd, NO);
		if (line && line[0] == '"')
		{
			width = ft_atoi(line + 1);
			height = ft_atoi(ft_strchr(line, ' '));
			texture = ft_create_canvas(width, height);
			break ;
		}
		free(line);
	}
	ft_load_xpm_to_matrix(&texture, xpm_file);
	get_next_line(fd, YES);
	close(fd);
	return (texture);
}

// Creates a new xpm pattern.
t_pattern	ft_create_xpm_pattern(int pattern_type, char *xpm_file)
{
	t_pattern	pattern;

	pattern.type = pattern_type;
	pattern.a = (t_color){0, 0, 0, 3};
	pattern.b = (t_color){0, 0, 0, 3};
	pattern.transform = ft_create_matrix(4, 4, YES);
	pattern.inverted = ft_create_matrix(4, 4, YES);
	pattern.xpm = ft_read_xpm(xpm_file);
	return (pattern);
}

// Returns the color of the xpm at the specified point.
t_color	ft_xpm_at(t_pattern pattern, t_point point)
{
	double	u;
	double	v;
	int		x;
	int		y;

	u = (point.x + 1.0) / 2.0;
	v = 1.0 - ((point.y + 1.0) / 2.0);
	x = (int)(u * (pattern.xpm.width - 1) + 0.5);
	y = (int)(v * (pattern.xpm.height - 1) + 0.5);
	return (pattern.xpm.pixels[y][x]);
}
