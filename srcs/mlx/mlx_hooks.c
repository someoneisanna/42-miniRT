/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:35:48 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/25 16:47:59 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_button_press(int k, t_world *img)
{
	if (k == 0xff1b)
		ft_close(img);
	return (0);
}

int	ft_close(t_world *w)
{
	mlx_destroy_image(w->mlx, w->img.img);
	mlx_destroy_window(w->mlx, w->win);
	mlx_destroy_display(w->mlx);
	free(w->mlx);
	ft_free_all_allocated_memory(w);
	exit(EXIT_SUCCESS);
}
