#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct camera
{
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
} camera;

// create a 'camera' which is basically the observer's point of view, 
// where the rays will be cast from
camera create_default_camera()
{
	float aspect_ratio = 16.0 / 9.0;

	// viewport is the area where the rays will be cast into
	float viewport_height = 2.0;
	float viewport_width = aspect_ratio * viewport_height;
	
	// focal_length is the distance between the camera and the viewport (z)
	float focal_length = 1.0; 

	camera ret = {0};
	ret.origin = (point3) {0.0, 0.0, 0.0};					// camera is at the origin (0,0,0)
	ret.horizontal = (vec3) {viewport_width, 0.0, 0.0};		// horizontal length of the viewport (x)
	ret.vertical = (vec3) {0.0, viewport_height, 0.0};		// vertical length of the viewport   (y)

	// lower_left_corner is the bottom left corner of the viewport
	ret.lower_left_corner = (vec3)
	{
		ret.origin.x - ret.horizontal.x / 2,				// x
		ret.origin.y - ret.vertical.y / 2,					// y
		-focal_length										// z
	};
	return (ret);
}

// get the ray that will be cast from the camera to the viewport
ray camera_get_ray(camera camera, float u, float v)
{
	// this is the same as: lower_left_corner + u * horizontal + v * vertical - origin
	ray ray = {0};

	vec3 temp1 = ft_op(camera.lower_left_corner, '+', ft_ops(camera.horizontal, '*', u));
	vec3 temp2 = ft_op(temp1, '+', ft_ops(camera.vertical, '*', v));
	vec3 temp3 = ft_op(temp2, '-', camera.origin);

	ray.direction = temp3;
	return (ray);
}

#endif