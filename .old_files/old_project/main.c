/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:23:47 by mamaral-          #+#    #+#             */
/*   Updated: 2024/04/17 14:55:02 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"
#include "scene.h"

/*
int	ft_button(int keycode, t_image *img)
{
	if (keycode == ESC)
		ft_close(img);
	return (0);
}

void	ft_mlx_pixel_put(t_image *data, int x, int y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = ft_int_to_rgb(color);
}
void	ft_write_panel(t_image *img, t_vec3 top_left, t_vec3 bottom_right, t_color clr)
{
	int	x;
	int	y;

	x = top_left.x - 1;
	while (++x < bottom_right.x + top_left.x)
	{
		y = top_left.y - 1;
		while (++y < bottom_right.y + top_left.y)
			ft_mlx_pixel_put(img, x, y, clr);
	}
}

int	ft_int_to_rgb(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = ft_limit_int(color.r, 0, 255);
	g = ft_limit_int(color.g, 0, 255);
	b = ft_limit_int(color.b, 0, 255);
	return (r << 16 | g << 8 | b);
}

void ft_init_color(t_minirt *prog)
{
	int	i;

	i = -1;
	while (++i < prog->cam.render_width)
	{
		prog->img.samp_color[i] = (t_color *)malloc(sizeof(t_color) * prog->cam.render_height);
		if (!prog->img.samp_color[i])
			ft_error("Error: malloc failed to allocate memory");
	}
}

void ft_create_scene(t_minirt *prog)
{
	ft_create_items(prog);
	if(!prog->cam.ambient_set)
		prog->cam.background = ft_put_rgb(55,55,55);
	ft_create_axis_box(prog);
	prog->ready = true;
}

void ft_paint_scene(t_minirt *prog)
{
	ft_init_color(prog);
	ft_create_scene(prog);
}

void ft_colortable(int nx, int ny, t_scene *scene)
{
	int		i;
	int		j;
	int		k;
	t_color	col;

	i = -1;
	j = ny;
	k = 0;
	scene->color = (int **)malloc(sizeof(int *) * ny);
	while (++i < ny)
		scene->color[i] = (int *)malloc(sizeof(int) * nx);
	while (--j >= 0)
	{
		i = -1;
		printf("Remaining: %d\n", j);
		while (++i < nx)
		{
			col = ft_ray_pixel(i, j, scene);
			scene->color[k][i] = ft_int_to_rgb(col);
		}
		k++;
	}
}

void ft_free_scene(t_scene *scene)
{
	t_elem *elem;
	t_elem *temp;

	elem = scene->light;
	temp = NULL;
	if (scene)
	{
		while (elem)
		{
			temp = elem;
			elem = elem->next;
			free(temp);
		}
		free(scene);
	}
}

void ft_init_offset(t_minirt *prog)
{
	prog->top_offset.img = mlx_new_image(prog->mlx, prog->cam.render_width, TOP_BAR);
	if (!prog->top_offset.img)
		ft_error("Error: mlx failed to create image");
	prog->top_offset.addr = mlx_get_data_addr(prog->top_offset.img, &prog->top_offset.bits_per_pixel, &prog->top_offset.line_length, &prog->top_offset.endian);
	prog->bottom_offset.img = mlx_new_image(prog->mlx, prog->cam.render_width, BOTTOM_BAR);
	if (!prog->bottom_offset.img)
		ft_error("Error: mlx failed to create image");
	prog->bottom_offset.addr = mlx_get_data_addr(prog->bottom_offset.img, &prog->bottom_offset.bits_per_pixel, &prog->bottom_offset.line_length, &prog->bottom_offset.endian);
	prog->update_ui = true;
}

void ft_init_hooks(t_minirt *prog)
{
	mlx_hook(prog->win, KeyPress, KeyPressMask, ft_button, prog);
	mlx_hook(prog->win, DestroyNotify, ButtonPressMask, ft_close, prog);
	// mlx_hook(prog->win, MotionNotify, PointerMotionMask, ft_mouse, prog);
	// mlx_hook(prog->win, ButtonPress, ButtonPressMask, ft_mouse_click, prog);

}

t_color	ft_put_rgb(int r, int g, int b)
{
	t_color	clr;

	clr.r = ft_limit_int(r, 0, 24576);
	clr.g = ft_limit_int(g, 0, 24576);
	clr.b = ft_limit_int(b, 0, 24576);
	clr.samples = 1;
	return (clr);
}

void	ft_draw_offset(t_minirt *prog)
{
	if(!prog->update_ui)
		return;
	prog->update_ui = false;
	ft_write_panel(&prog->top_offset, ft_vec3_create(0,0,0), ft_vec3_create(prog->cam.render_width, TOP_BAR, 0), ft_put_rgb(35,35,35));
	ft_write_panel(&prog->top_offset, ft_vec3_create(5,5,0), ft_vec3_create(prog->cam.render_width - 10, 20, 0), ft_put_rgb(65,65,65));
	mlx_put_image_to_window(prog->mlx, prog->win, prog->top_offset.img, 0, 0);
	mlx_string_put(prog->mlx, prog->win, 10, 19, 0xAAAAAA, "Scene : ");
	mlx_string_put(prog->mlx, prog->win, 55, 19, 0xAAAAAA, "miniRT");
	ft_write_panel(&prog->bottom_offset, ft_vec3_create(0,0,0), ft_vec3_create(prog->cam.render_width, BOTTOM_BAR, 0), ft_put_rgb(35,35,35));
	ft_write_panel(&prog->bottom_offset, ft_vec3_create(5,5,0), ft_vec3_create(prog->cam.render_width - 60, BOTTOM_BAR - 10, 0), ft_put_rgb(65,65,65));
	mlx_put_image_to_window(prog->mlx, prog->win, prog->bottom_offset.img, 0, ft_max(prog->cam.render_height, 650) + TOP_BAR);
	mlx_string_put(prog->mlx, prog->win, prog->cam.render_width - 29, prog->cam.render_height + TOP_BAR + 14, 0xAAAAAA, "0");
	//add buttons
}

void	ft_start_program(t_minirt *prog)
{
	ft_bzero(prog, sizeof(t_minirt));
	create_default_camera(&prog->cam);
	prog->scene.resol = (t_resol){WIDTH, (int)(WIDTH / RATIO)}; // the parser should fill this (rn, it is taking it from .rt)
	prog->mlx = mlx_init();
	prog->win = mlx_new_window(prog->mlx, prog->scene.resol.x, prog->scene.resol.y, "miniRT");
	if(!prog->mlx || !prog->win)
		ft_error("Error: mlx failed to initialize");
	prog->img.img = mlx_new_image(prog->mlx, prog->cam.render_width, prog->cam.render_height);
	if (!prog->img.img)
		ft_error("Error: mlx failed to create image");
	prog->img.addr = mlx_get_data_addr(prog->img.img, &prog->img.bits_per_pixel, &prog->img.line_length, &prog->img.endian);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, TOP_BAR);
	prog->img.samp_color = (t_color **)malloc(sizeof(t_color *) * prog->cam.render_width);
	if (!prog->img.samp_color)
		ft_error("Error: malloc failed to allocate memory");
	ft_init_offset(prog);
	ft_init_hooks(prog);
	// mlx_loop_hook(mlx(), ft_update, NULL);
	ft_draw_offset(prog);
	ft_paint_scene(prog);
	mlx_loop(prog->mlx);
}
*/

int	main(int ac, char **av)
{
	(void)ac;
	//t_minirt	img;
	(void)av;
	printf("Hello, World!\n");
	//open_file(av[1], &img.scene); // must accept "ac" to check conditions where arguments are more or less than 2
	//ft_start_program(&img);
	//return (0);
	// ft_colortable(WIDTH, HEIGHT, &scene);
	
	// ft_write_panel(&img, &scene);
	// ft_free_scene(&scene);
}