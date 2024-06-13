#include "exercises.h"

Projectile	tick(Environment env, Projectile proj)
{
	t_vec3		position;
	t_vec3		velocity;
	Projectile	new_proj;

	position = ft_op(proj.position, '+', proj.velocity);
	velocity = ft_op(proj.velocity, '+', ft_op(env.gravity, '+', env.wind));
	new_proj = (Projectile){position, velocity};
	return (new_proj);
}

void	ft_projectile(t_world *prog, int width, int height)
{
	int			x;
	int			y;
	int			cor;
	t_canvas	canvas;
	Projectile	p;
	Environment	e;

	p = (Projectile){ft_point(0, 1, 0), ft_ops(ft_normalize(ft_vector(1, 1.8,
					0)), '*', 11.25)};
	e = (Environment){ft_vector(0, -0.13, 0), ft_vector(-0.02, 0, 0)};
	canvas = ft_create_canvas(width, height);
	y = 0;
	prog->img.color = malloc(height * sizeof(int *));
	while (y < height)
	{
		x = 0;
		prog->img.color[y] = malloc(width * sizeof(int));
		while (x < width)
		{
			while (p.position.y > 0)
			{
				p = tick(e, p);
				cor = height - p.position.y;
				for (int dy = -2; dy <= 2; dy++)
				{
					for (int dx = -2; dx <= 2; dx++)
					{
						if (p.position.x + dx >= 0 && p.position.x
							+ dx < width && cor + dy >= 0 && cor
							+ dy < height)
						{
							ft_write_pixel(canvas, p.position.x + dx, cor + dy,
								ft_color(1, 0, 0));
						}
					}
				}
			}
			x++;
		}
		y++;
	}
	ft_panel_window(&prog->img, width, height, canvas.pixels);
}
