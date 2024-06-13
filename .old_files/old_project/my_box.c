#include "minirt.h"
#include <stdlib.h>

/*
t_room	*createRoom(int length, int width, double proportion)
{
	t_room	*room;

	room = malloc(sizeof(t_room));
	room->sizex = length;
	room->sizey = width;
	room->width = width * proportion;
	room->height = length * proportion;
	room->depth = (width - room->width) / 2;
	room->top_left_x = room->depth;
	room->top_left_y = (length - room->height) / 2;
	room->top_right_x = room->depth;
	room->top_right_y = (length + room->height) / 2;
	room->bottom_left_x = room->depth + room->width;
	room->bottom_left_y = (length - room->height) / 2;
	room->bottom_right_x = room->depth + room->width;
	room->bottom_right_y = (length + room->height) / 2;
	return (room);
}

int	ft_roof_floor(t_room *room, int i, int j)
{
	int	size;
	int	image;

	image = 0;
	if (i < room->top_left_x)
	{
		size = room->sizex - (room->sizex - room->height) * i
			/ room->top_left_x;
		if (j >= room->sizex / 2 - size / 2 && j < room->sizex / 2 + size / 2)
			image = COLOR_ROOF;
	}
	else if (i >= room->top_left_x + room->width)
	{
		size = room->sizex - (room->sizex - room->height) * (room->sizey - i)
			/ room->top_left_x;
		if (j >= room->sizex / 2 - size / 2 && j < room->sizex / 2 + size / 2)
			image = COLOR_FLOOR;
	}
	return (image);
}

int	ft_walls(t_room *room, int i, int j)
{
	int	image;
	int	size;

	image = ft_roof_floor(room, i, j);
	if (j < room->top_left_y)
	{
		size = room->sizey - (room->sizey - room->width) * j / room->top_left_y;
		if (i >= room->sizey / 2 - size / 2 && i < room->sizey / 2 + size / 2)
			image = COLOR_LEFT_WALL;
	}
	else if (j >= room->top_left_y + room->height)
	{
		size = room->sizey - (room->sizey - room->width) * (room->sizex - j)
			/ room->top_left_y;
		if (i >= room->sizey / 2 - size / 2 && i < room->sizey / 2 + size / 2)
			image = COLOR_RIGHT_WALL;
	}
	return (image);
}

int	**createImage(t_room *room)
{
	int **image;
	int i;
	int j;

	i = -1;
	image = malloc(room->sizey * sizeof(int *));
	while (++i < room->sizey)
		image[i] = malloc(room->sizex * sizeof(int));

	i = -1;
	while (++i < room->sizey)
	{
		j = -1;
		while (++j < room->sizex)
		{
			if (i >= room->top_left_x && i < room->top_left_x + room->width
				&& j >= room->top_left_y && j < room->top_left_y + room->height)
				image[i][j] = COLOR_BACKGROUND;
			else
				image[i][j] = ft_walls(room, i, j);
		}
	}
	return (image);
}
*/