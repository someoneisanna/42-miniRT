#ifndef EXERCISES_H
# define EXERCISES_H

# include "minirt.h"

// # define XPM_FILE "./brick_clr.xpm"
# define XPM_FILE "./wall.xpm"
# define XPM_FILE2 "./jabu.xpm"
# define XPM_FILE3 "./earth.xpm"
typedef struct
{
	t_vec3	position;
	t_vec3	velocity;
}			Projectile;

typedef struct
{
	t_vec3	gravity;
	t_vec3	wind;
}			Environment;

Projectile	tick(Environment env, Projectile proj);
void		ft_projectile(t_world *prog, int width, int height);

void		draw_clock_hands(t_vec3 *hour_hand, t_vec3 *minute_hand,
				t_vec3 *second_hand);
void		draw_line(t_world *clock, t_vec3 p1, t_vec3 p2, t_color color);
void		draw_clock_face(t_world *clock, int width, int height);
void		ft_crazy_clock(t_world *clock);

void		ft_print_circle(t_world *print);

void		ft_print_sphere(t_world *treedee);

void	ft_spereres(t_shapes **s1, t_shapes **s2, t_shapes **s3);
void	ft_cube(t_shapes **floor, t_shapes **l_wall, t_shapes **r_wall);
void	ft_print_room(t_world *room);
void	ft_chapter_9(t_world *w);
void	ft_chapter_10(t_world *w);
void	ft_multiple_lights(t_world *w);
void	ft_snowman(t_world *w);
void	ft_reflection(t_world *w);
void	ft_refraction(t_world *w);
void	ft_triangle(t_world *w);

#endif
