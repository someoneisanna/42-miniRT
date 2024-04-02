#include <stdio.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "camera.h"
#include "utils.h"
#include "material.h"

color ray_color(ray r, hittable *world, int world_size, int depth)
{
	hit_record rec = {0};
	if (depth <= 0)
		return ((color) {0, 0, 0});
	if (hittable_list_hit(world, world_size, r, 0.0001, INFINITY, &rec))
	{
		color attenuation;
		ray scattered;
		if (material_scatter(rec.material, r, &rec, &attenuation, &scattered))
			return (vec3_mult_element_wise(attenuation, ray_color(scattered, world, world_size, depth - 1)));
		return ((color) {0, 0, 0});
	}
	vec3 unit_direction = vec3_normalized(r.direction);
	float t = 0.5 * (unit_direction.y + 1.0);
	return (vec3_sum(
		vec3_mult_scalar((color) {1.0, 1.0, 1.0}, 1.0 - t), 
		vec3_mult_scalar((color) {0.5, 0.7, 1.0}, t)));
}

int main(int argc, char *argv[])
{
	float aspect_ratio = 16.0 / 9.0;
	int width = 400;
	int height = (int) (width/aspect_ratio);
	int samples_per_pixel = 100;
	int max_depth = 20;

	int world_size = 4;
	hittable world[world_size];

	lambertian l1 = create_lambertian((vec3) {0.8, 0.8, 0.0});
	lambertian l2 = create_lambertian((vec3) {0.7, 0.3, 0.3});
	metal m1 = create_metal((vec3) {0.8, 0.8, 0.8}, 0.3);
	metal m2 = create_metal((vec3) {0.8, 0.6, 0.2}, 1.0);

	world[0] = (hittable) create_sphere((point3) {0.0, -100.5, -1.0}, 100, (material*) &l1);
	world[1] = (hittable) create_sphere((point3) {0.0, 0.0, -1.0}, 0.5, (material*) &l2);
	world[2] = (hittable) create_sphere((point3) {1.0, 0.0, -1.0}, 0.5, (material*) &m1);
	world[3] = (hittable) create_sphere((point3) {-1.0, 0.0, -1.0}, 0.5, (material*) &m2);

	camera camera = create_default_camera();

	printf("P3\n%d %d 255\n",width,height);

	for (int i = height - 1; i >= 0; i--)
	{
		fprintf(stderr, "Remaining %d\n", i);
		for (int j = 0; j < width; j++)
		{
			color pixel_color = {0};
			for (int s = 0; s < samples_per_pixel; s++)
			{
				float u = ((double) j + random_float_min_max(0, 2)) / (width - 1);
				float v = ((double) i + random_float_min_max(0, 2)) / (height - 1);
				ray r = camera_get_ray(camera, u, v);
				pixel_color = vec3_sum(pixel_color, ray_color(r, world, world_size, max_depth));
			}
			write_color(stdout, pixel_color, samples_per_pixel);
		}
	}
	fprintf(stderr, "Done\n");
}