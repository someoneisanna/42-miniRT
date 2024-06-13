#include "exercises.h"
#include <time.h>

// #define PI 3.14159265

// Function to draw the clock hands
void	draw_clock_hands(t_vec3 *hour_hand, t_vec3 *minute_hand, t_vec3 *second_hand)
{
    // Get the current time
    time_t now = time(NULL); // FORBIDDEN FUNCTION 
    struct tm *t = localtime(&now); // FORBIDDEN FUNCTION 

    // Calculate the angles of rotation in radians
    double hour_angle = (t->tm_hour % 12) * 2 * PI / 12;
    double minute_angle = t->tm_min * 2 * PI / 60;
    double second_angle = t->tm_sec * 2 * PI / 60;
	// double hour_angle = 2 * PI - ((t->tm_hour % 12) * 2 * PI / 12 + t->tm_min * 2 * PI / (12 * 60)) - PI / 2;
    // double minute_angle = 2 * PI - (t->tm_min * 2 * PI / 60) - PI / 2;
    // double second_angle = 2 * PI - (t->tm_sec * 2 * PI / 60) - PI / 2;


    // Create rotation matrices
    t_matrix hour_rotation = ft_create_rotation_matrix('z', hour_angle);
    t_matrix minute_rotation = ft_create_rotation_matrix('z', minute_angle);
    t_matrix second_rotation = ft_create_rotation_matrix('z', second_angle);

    // Calculate the new positions of the hands
    *hour_hand = ft_multiply_matrix_tuple(hour_rotation, *hour_hand);
    *minute_hand = ft_multiply_matrix_tuple(minute_rotation, *minute_hand);
    *second_hand = ft_multiply_matrix_tuple(second_rotation, *second_hand);
}

void draw_line(t_world *clock, t_vec3 p1, t_vec3 p2, t_color color)
{
	t_vec3 delta = ft_op(p1, '-', p2);
	double length = sqrt(delta.x * delta.x + delta.y * delta.y);
	double step_x = delta.x / length;
	double step_y = delta.y / length;
	double x = p1.x;
	double y = p1.y;

	for (int i = 0; i < length; i++)
	{
		ft_write_pixel(clock->canvas, x, y, color);
		x += step_x;
		y += step_y;
	}
}

void draw_clock_face(t_world *clock, int width, int height)
{
    t_vec3 center = {width/2, height/2, 0, 1};

    // Calculate the radius of the clock face based on the smaller dimension
    int radius = (width < height ? width : height) / 2 - 20;

    // Draw the clock face
    for (int i = 0; i < 12; i++)
    {
        double angle = i * 2 * PI / 12;
        t_vec3 p1 = {center.x + radius * cos(angle), center.y + radius * sin(angle), 0, 1};
        t_vec3 p2 = {center.x + (radius - 20) * cos(angle), center.y + (radius - 20) * sin(angle), 0, 1};
        draw_line(clock, p1, p2, ft_color(1, 1, 1));
    }
}
void	ft_crazy_clock(t_world *clock)
{
	int height = WIDTH/RATIO;
	t_vec3 center = {WIDTH/2, height/2, 0, 1};
	int hand_length = (WIDTH < height ? WIDTH : height) / 2 - 20;
	clock->canvas = ft_create_canvas(WIDTH, height);
    t_vec3 hour_hand = {0, -hand_length, 0, 1};
    t_vec3 minute_hand = {0, -hand_length, 0, 1};
    t_vec3 second_hand = {0, -hand_length, 0, 1};
	draw_clock_face(clock, WIDTH, height);
	draw_clock_hands(&hour_hand, &minute_hand, &second_hand);
	
	t_vec3 hour_hand_pos = {center.x + hour_hand.x, center.y + hour_hand.y, 0, 1};
    t_vec3 minute_hand_pos = {center.x + minute_hand.x, center.y + minute_hand.y, 0, 1};
    t_vec3 second_hand_pos = {center.x + second_hand.x, center.y + second_hand.y, 0, 1};

    draw_line(clock, center, hour_hand_pos, ft_color(1, 0, 0));
    draw_line(clock, center, minute_hand_pos, ft_color(0, 1, 0));
    draw_line(clock, center, second_hand_pos, ft_color(0, 0, 1));
    ft_panel_window(&clock->img, WIDTH, height, clock->canvas.pixels);
	ft_panel_window(&clock->img, WIDTH, height, clock->canvas.pixels);
}
