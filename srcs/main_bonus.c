/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:32:29 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/30 17:24:56 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_world	w;

	if (ac != 2)
		ft_perror(NULL, "Invalid number of arguments");
	ft_bzero(&w, sizeof(t_world));
	w.width = WIDTH;
	w.height = WIDTH / RATIO;
	ft_parser(av[1], &w);
	w.camera = ft_create_camera(w.width, w.height, w.cam_fov * DEG2RAD);
	w.camera->transform = ft_view_transform_matrix(w.cam_coords,
			ft_op(w.cam_orient, '+', w.cam_coords), (t_point){0, 1, 0, 0});
	w.camera->inverted = ft_invert_matrix(w.camera->transform);
	w.cam_reset = w.camera->transform;
	ft_set_ui(&w);
	/*printf("sp: %p\n", w.ui.sp);
	printf("pl: %p\n", w.ui.pl);
	printf("cy: %p\n", w.ui.cy);
	printf("co: %p\n", w.ui.co);
	printf("cb: %p\n", w.ui.cb);
	printf("tr: %p\n", w.ui.tr);
	printf("li: %p\n", w.ui.li[0]);
	printf("li: %p\n", w.ui.li[1]);
	printf("li: %p\n", w.ui.li[2]);*/
	ft_open_window(&w);
	ft_render_threads(w.camera, &w);
	ft_set_hooks(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	mlx_loop(w.mlx);
}
