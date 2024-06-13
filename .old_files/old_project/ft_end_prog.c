#include "minirt.h"

/*
void	ft_free_all_allocated_memory(t_image *test)
{
	int	i;

	i = 0;
	while (i < (int)(WIDTH / RATIO))
	{
		free(test->color[i]);
		i++;
	}
	free(test->color);
}

int	ft_close(t_image *test)
{
	mlx_destroy_image(test->mlx, test->img);
	mlx_destroy_window(test->mlx, test->win);
	mlx_destroy_display(test->mlx);
	free(test->mlx);
	ft_free_all_allocated_memory(test);
	printf("CLOSED\n");
	exit(EXIT_SUCCESS);
}
*/