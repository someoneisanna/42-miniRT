#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include "vec3.h"

void write_color(FILE *__stream, color pixel_color, int samples)
{
	pixel_color = vec3_mult_scalar(pixel_color, (float) 1.0 / samples);
	pixel_color.r = sqrt(pixel_color.r);
	pixel_color.g = sqrt(pixel_color.g);
	pixel_color.b = sqrt(pixel_color.b);
	int ir = (int) (255 * pixel_color.r);
	int ig = (int) (255 * pixel_color.g);
	int ib = (int) (255 * pixel_color.b);
	fprintf(__stream, "%d %d %d\n", ir, ig, ib);
}

#endif