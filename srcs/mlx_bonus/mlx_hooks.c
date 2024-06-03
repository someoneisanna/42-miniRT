/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:35:48 by ataboada          #+#    #+#             */
/*   Updated: 2024/06/03 18:34:11 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_set_hooks(t_world *w)
{
	mlx_do_key_autorepeatoff(w->mlx);
	mlx_hook(w->win, KeyPress, KeyPressMask, ft_button_press, w);
	mlx_hook(w->win, KeyRelease, KeyReleaseMask, ft_button_release, w);
	mlx_hook(w->win, DestroyNotify, ButtonPressMask, ft_close, w);
	mlx_loop_hook(w->mlx, ft_update, w);
}

int	ft_button_press(int k, t_world *img)
{
	if (k == 0xff1b)
		ft_close(img);
	else if (k == W || k == A || k == S || k == D
		|| k == UP || k == DOWN || k == LEFT || k == RIGHT
		|| k == ALT || k == SPACE || k == PLUS || k == MINUS
		|| k == R || k == O || k == L || k == Z)
	{
		if (k == O && img->oflag == 0)
			img->oflag = 1;
		else if (k == O && img->oflag == 1)
			img->oflag = 0;
		else if (k == L && img->lflag == 0)
			img->lflag = 1;
		else if (k == L && img->lflag == 1)
			img->lflag = 0;
		else if (k == R && img->rflag == 0)
			img->rflag = 1;
		else if (k == R && img->rflag == 1)
			img->rflag = 0;
		img->status_key = k;
	}
	return (0);
}

int	ft_button_release(int k, t_world *img)
{
	if (img->status_key == k)
		img->status_key -= k;
	return (0);
}

int	ft_close(t_world *w)
{
	mlx_destroy_image(w->mlx, w->img.img);
	mlx_destroy_window(w->mlx, w->win);
	mlx_destroy_display(w->mlx);
	free(w->mlx);
	ft_free_ui(w);
	ft_free_all_allocated_memory(w);
	exit(EXIT_SUCCESS);
}
