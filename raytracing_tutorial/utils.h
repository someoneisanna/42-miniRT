#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

float random_float() 
{
	return ((float) rand() / (RAND_MAX + 1.0));
}

float random_float_min_max(float min, float max) 
{
	return (min + (max - min) * random_float());
}

#endif