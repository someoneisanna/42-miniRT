/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:43:20 by ataboada          #+#    #+#             */
/*   Updated: 2024/05/29 11:44:00 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_set_ui(t_world *w)
{
	if (w->ui.n_sp > 0)
		w->ui.sp = malloc(sizeof(t_sphere *) * w->ui.n_sp);
	if (w->ui.n_pl > 0)
		w->ui.pl = malloc(sizeof(t_plane *) * w->ui.n_pl);
	if (w->ui.n_cy > 0)
		w->ui.cy = malloc(sizeof(t_cylinder *) * w->ui.n_cy);
	if (w->ui.n_co > 0)
		w->ui.co = malloc(sizeof(t_cone *) * w->ui.n_co);
	if (w->ui.n_cb > 0)
		w->ui.cb = malloc(sizeof(t_cube *) * w->ui.n_cb);
	if (w->ui.n_tr > 0)
		w->ui.tr = malloc(sizeof(t_triangle *) * w->ui.n_tr);
	if (w->ui.n_li > 0)
		w->ui.li = malloc(sizeof(t_light *) * w->ui.n_li);
	ft_set_arrays(w);
}

void	ft_set_arrays(t_world *w)
{
	t_list	*tmp;

	tmp = w->objects;
	while (tmp)
	{
		if (((t_shapes *)tmp->content)->type == SPHERE)
			w->ui.sp[w->i[0]++] = (t_sphere *)tmp->content;
		else if (((t_shapes *)tmp->content)->type == PLANE)
			w->ui.pl[w->i[1]++] = (t_plane *)tmp->content;
		else if (((t_shapes *)tmp->content)->type == CYLINDER)
			w->ui.cy[w->i[2]++] = (t_cylinder *)tmp->content;
		else if (((t_shapes *)tmp->content)->type == CONE)
			w->ui.co[w->i[3]++] = (t_cone *)tmp->content;
		else if (((t_shapes *)tmp->content)->type == CUBE)
			w->ui.cb[w->i[4]++] = (t_cube *)tmp->content;
		else if (((t_shapes *)tmp->content)->type == TRIANGLE)
			w->ui.tr[w->i[5]++] = (t_triangle *)tmp->content;
		tmp = tmp->next;
	}
	tmp = w->lights;
	while (tmp)
	{
		w->ui.li[w->i[6]++] = (t_light *)tmp->content;
		tmp = tmp->next;
	}
}

void	ft_free_ui(t_world *w)
{
	if (w->ui.n_sp > 0)
		free(w->ui.sp);
	if (w->ui.n_pl > 0)
		free(w->ui.pl);
	if (w->ui.n_cy > 0)
		free(w->ui.cy);
	if (w->ui.n_co > 0)
		free(w->ui.co);
	if (w->ui.n_cb > 0)
		free(w->ui.cb);
	if (w->ui.n_tr > 0)
		free(w->ui.tr);
	if (w->ui.n_li > 0)
		free(w->ui.li);
}
