#ifndef BOX_H
# define BOX_H

# include "minirt.h"
# include "vectors.h"

# define COLOR_BACKGROUND 0xFF00FF
# define COLOR_ROOF 0xff0000
# define COLOR_FLOOR 0x00ff00
# define COLOR_LEFT_WALL 0x0000ff
# define COLOR_RIGHT_WALL 0xFFFF00

typedef struct s_room
{
	int sizex;
	int sizey;
	int width;
	int height;
	int depth;
	int top_left_x;
	int top_left_y;
	int top_right_x;
	int top_right_y;
	int bottom_left_x;
	int bottom_left_y;
	int bottom_right_x;
	int bottom_right_y;
} t_room;

// int** createImage(int length, int width, double proportion);
int** createImage(t_room *room);
t_room *createRoom(int length, int width, double proportion);

#endif