#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include "vec3.h"

// this function will write the color to the file 
void write_color(FILE *restrict __stream, color pixel_color, int samples)
{
	pixel_color = ft_ops(pixel_color, '*', (float) 1.0 / samples);
	
	// we will use gamma correction to make the image look more realistic
	// it should make the image have more contrast. in our case, we just 
	// raise the color to the power of 1/gamma, which is 2 in our case.
	pixel_color.r = sqrt(pixel_color.r);
	pixel_color.g = sqrt(pixel_color.g);
	pixel_color.b = sqrt(pixel_color.b);

	int ir = (int) (255 * pixel_color.r);
	int ig = (int) (255 * pixel_color.g);
	int ib = (int) (255 * pixel_color.b);

	fprintf(__stream, "%d %d %d\n", ir, ig, ib);
}

void write_color_to_buffer (uint8_t *buffer, int cur, color color, int samples)
{
	color = ft_ops(color, '*', (float) 1 / samples);
	
	color.r = sqrt (color.r);
	color.g = sqrt (color.g);
	color.b = sqrt (color.b);

	buffer[cur++] = (uint8_t) (color.r * 255);
	buffer[cur++] = (uint8_t) (color.g * 255);
	buffer[cur] = (uint8_t) (color.b * 255);
}

#endif