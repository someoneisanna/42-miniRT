#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

float random_float(unsigned int *seed) 
{
	return ((float) rand_r(seed) / (RAND_MAX + 1.0));
} 

float random_float_min_max(unsigned int *seed, float min, float max) 
{
	return (min + (max - min) * random_float(seed));
}

#endif