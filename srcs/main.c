/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:43:54 by ataboada          #+#    #+#             */
/*   Updated: 2024/06/07 11:19:52 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_world	w;

	if (ac != 2)
		ft_perror(NULL, NULL, "Invalid number of arguments");
	ft_bzero(&w, sizeof(t_world));
	w.width = WIDTH;
	w.height = WIDTH / RATIO;
	ft_parser(av[1], &w);
	ft_open_window(&w);
	ft_render(w.camera, &w);
	ft_set_hooks(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	mlx_loop(w.mlx);
}

// TODO:
// - OK do the camera
// - OK norminette
// - clean code (check michel's tip to see what is making the program slow)
// - solve leaks (parser -still reachable- and check for program leaks)
// - check for errors

// - parser for bonus
// - threads for bonus
// - anti-aliasing for bonus
// - build new scenes and perform tests

// - UI
// - buttons for resolution, x, y, z, + and -
// - update ft_update to move the objects
// - string colors
// - add flags to use + and -: 1 to save the old str, 1 to store the new str and
// 1 to check if it relates to xyz
// - array to store the pointer to objects
// - norminette
