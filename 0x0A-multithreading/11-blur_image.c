#include "multithreading.h"

/**
 * create_portions - Create chunks to send to threads
 * @img_blur: Holds the address at which the blured image is stored
 * @img:      Points to the source image
 * @kernel:   Points to the convolution kernel to use
 *
 * Return: A pointer with portions of Struct blur_portion_t
 */
blur_portion_t *create_portions(img_t *img_blur, img_t const *img,
				kernel_t const *kernel)
{
	blur_portion_t *portion = NULL;
	size_t piece_h = 0;
	int i = 0;

	portion = calloc(sizeof(blur_portion_t), THREADS);
	if (!portion)
		return (NULL);

	for (; i < THREADS;
	 i++, piece_h += img->h / THREADS)
	{
		portion[i].img = img;
		portion[i].img_blur = img_blur;
		portion[i].kernel = kernel;
		portion[i].w = img->w;
		portion[i].h = img->h / THREADS;
		portion[i].x = 0;
		portion[i].y = piece_h;
	}
	portion[i - 1].h += 4;
	return (portion);
}

/**
 * assign_thread - Assign task to Thread
 * @portion: Pointer to portion of struct blur_portion_t
 *
 * Return: Nothing
 */
void *assign_thread(void *portion)
{
	blur_portion((blur_portion_t *)portion);
	pthread_exit(NULL);
}

/**
 * blur_image - Blurs the entirety of an image using a Gaussian Blur
 * with Multithreading
 * @img_blur: Holds the address at which the blured image is stored
 * @img:      Points to the source image
 * @kernel:   Points to the convolution kernel to use
 *
 * Return: Nothing
 */
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel)
{
	blur_portion_t *portion = NULL;
	pthread_t tid[THREADS];
	int i = 0;

	portion = create_portions(img_blur, img, kernel);
	for (; i < THREADS; i++)
	{
		if (pthread_create(&tid[THREADS], NULL, (&assign_thread), portion + i) != 0)
		{
			fprintf(stderr, "Error: Can not create prthread\n");
			return;
		}
		pthread_join(tid[THREADS], NULL);
	}

}
