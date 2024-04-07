#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "camera.h"
#include "utils.h"
#include "material.h"

typedef struct image
{
	uint8_t *data;
	int width;
	int height;
} image;

color ray_color(ray r, hittable_list *world, int depth, unsigned int *seed)
{
	hit_record rec = {0};
	if (depth <= 0)
		return ((color) {0, 0, 0});
	if (hittable_list_hit(world, r, 0.0001, INFINITY, &rec))
	{
		color attenuation;
		ray scattered;
		color emitted = material_emit(rec.material);
		if (!material_scatter(rec.material, r, &rec, &attenuation, &scattered, seed))
			return emitted;
		else
			return vec3_sum(emitted, vec3_mult_element_wise(attenuation, ray_color(scattered, world, depth - 1, seed)));
		return ((color) {0, 0, 0});
	}
	vec3 unit_direction = vec3_normalized(r.direction);
	float t = 0.5 * (unit_direction.y + 1.0);
	return (color) {0, 0, 0};
}

void render_image(unsigned int *seed, image *img, int initial_height, int final_height, int samples_per_pixel, camera camera, hittable_list *world, int max_depth)
{
	for (int i = initial_height; i < final_height; i++)
	{
		fprintf (stderr, "Remaining %d\n", img->height - 1 - i);
		for (int j = 0; j < img->width; j++)
		{
			int cur = (i * img->width + j) * 3;
			color pixel_color = { 0 };
			for (int s = 0; s < samples_per_pixel; s++)
			{
				float u = ((double) j + random_float_min_max (seed, 0., 2.)) / (img->width - 1);
				float v = 1. - ((double) i + random_float_min_max (seed, 0., 2.)) / (img->height - 1);
				ray ray = camera_get_ray (camera, u, v);
				pixel_color = vec3_sum (pixel_color, ray_color (ray, world, max_depth, seed));
			}
			write_color_to_buffer ((uint8_t *) img->data, cur, pixel_color, samples_per_pixel);
		}
	}
}

typedef struct render_context
{
	unsigned int seed;
	image *image;
	int initial_height;
	int final_height;
	int samples_per_pixel;
	camera camera;
	hittable_list *world;
	int max_depth;
} render_context;

render_context create_render_context(unsigned int seed, image *img, int initial_height, int final_height, int samples_per_pixel, camera camera, hittable_list *world, int max_depth)
{
	render_context ret = { 0 };
	ret.seed = seed;
	ret.image = img;
	ret.initial_height = initial_height;
	ret.final_height = final_height;
	ret.samples_per_pixel = samples_per_pixel;
	ret.camera = camera;
	ret.world = world;
	ret.max_depth = max_depth;
	return ret;
}

void *routine(void *arg)
{
	render_context *context = (render_context *) arg;
	render_image (&context->seed, context->image, context->initial_height,
		context->final_height, context->samples_per_pixel,
		context->camera, context->world, context->max_depth);
	return NULL;
}

int main(int argc, char *argv[])
{
	float aspect_ratio = 16.0 / 9.0;
	int width = 800;
	int height = (int) (width/aspect_ratio);
	int samples_per_pixel = 100;
	int max_depth = 5;

	int world_size = 5;
	hittable objects[world_size];
	hittable_list world;
	world.data = &objects[0];
	world.size = world_size;

	material m_ground = (material) create_lambertian((vec3) {0.8, 0.8, 0.0});
	material m_left = (material) create_dielectric(1.5);
	material m_center = (material) create_diffuse_light((color) {1.0, 1.0, 1.0});
	material m_right = (material) create_metal((vec3) {0.8, 0.3, 0.2}, 0.0);

	world.data[0] = (hittable) create_sphere((point3) {0.0, -100.5, -1.0}, 100, &m_ground);
	world.data[1] = (hittable) create_sphere((point3) {0.0, 200.0, -1.0}, 100, &m_center);
	world.data[2] = (hittable) create_sphere((point3) {-1.0, 0.0, -1.0}, -0.3, &m_left);
	world.data[3] = (hittable) create_sphere((point3) {-1.0, 0.0, -1.0}, 0.5, &m_left);
	world.data[4] = (hittable) create_sphere((point3) {1.0, 0.0, -1.0}, 0.5, &m_right);

	camera cam = create_default_camera();

	printf("P6\n%d %d 255\n",width,height);

	uint8_t buffer[width * height * 3];
	image img = {0};
	img.data = &buffer[0];
	img.width = width;
	img.height = height;

	int n_threads = 10;
	pthread_t pool[n_threads];
	render_context context_list[n_threads];

	for (int i = 0; i < n_threads; i++)
		context_list[i] = create_render_context(i, &img, i * height / n_threads, (i + 1) * height / n_threads, samples_per_pixel, cam, &world, max_depth);
	for (int i = 0; i < n_threads; i++)
		pthread_create(&pool[i], NULL, routine, &context_list[i]);
	for (int i = 0; i < n_threads; i++)
		pthread_join(pool[i], NULL);

	fwrite(&buffer[0], sizeof(buffer),1, stdout);
	fprintf(stderr, "Done\n");
}