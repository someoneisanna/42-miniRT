/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:33:41 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/25 16:48:25 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_open_window(t_world *w)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, w->width, w->height, "MiniRT");
	if (!w->win || !w->mlx)
	{
		ft_putstr_fd("Error\nFailed to start program.\n", 1);
		exit(1);
	}
	w->img.img = mlx_new_image(w->mlx, w->width, w->height);
	if (!w->img.img)
	{
		ft_putstr_fd("Error\nFailed to create image.\n", 1);
		exit(1);
	}
	w->img.addr = mlx_get_data_addr(w->img.img, &w->img.bpp,
			&w->img.line_length, &w->img.endian);
}

void	ft_panel_window(t_image *data, int x, int y, t_color **color)
{
	int		i;
	int		j;
	char	*dst;

	i = -1;
	while (++i < y)
	{
		j = -1;
		while (++j < x)
		{
			dst = data->addr + (i * data->line_length + j * (data->bpp / 8));
			*(unsigned int *)dst = ft_int_to_rgb(color[i][j]);
		}
	}
}
