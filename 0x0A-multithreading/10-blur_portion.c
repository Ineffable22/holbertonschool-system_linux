#include "multithreading.h"

/**
* blur_portion - Blurs a portion of an image using a Gaussian Blur.
* @portion: Points to a data structure described in the project requirements
*
* Return: Nothing
*/
void blur_portion(blur_portion_t const *portion)
{
	size_t y = 0, x = 0;

	if (!portion || !portion->img || !portion->img_blur ||
	    !portion->kernel || !portion->kernel->matrix)
		return;

	for (y = portion->y; y < portion->h + portion->y; y++)
		for (x = portion->x; x < portion->w + portion->x; x++)
			insert_blur(portion->img, portion->img_blur, portion->kernel, x, y);
}

/**
 * insert_blur - Insert pixels with Gaussian Blur
 * @img: Pointer to source Struct img_t
 * @new_img: Pointer to dest Struct img_t
 * @kernel: Pointer to Struct kernel_t
 * @x: x-coordinate
 * @y: y-coordinate
 *
 * Return: Nothing
 */
void insert_blur(const img_t *img, img_t *new_img, const kernel_t *kernel,
		 size_t x, size_t y)
{
	float divider = 0, avg_r = 0, avg_g = 0, avg_b = 0;
	ssize_t pos_x = 0, pos_y = 0;
	size_t pos_i = 0, radius = 0, i = 0, j = 0;

	if (!img || !new_img || !kernel || x > img->w || y > img->h)
		return;

	radius = kernel->size / 2;
	for (pos_y = (ssize_t)y - radius; i < kernel->size; i++, pos_y++)
		for (j = 0, pos_x = (ssize_t)x - radius; j < kernel->size; j++, pos_x++)
		{
			if ((pos_x >= 0 && (size_t)pos_x < img->w) &&
			    (pos_y >= 0 && (size_t)pos_y < img->h))
			{
				divider += kernel->matrix[i][j];
				pos_i = (pos_y * img->w) + pos_x;
				avg_r += img->pixels[pos_i].r * kernel->matrix[i][j];
				avg_g += img->pixels[pos_i].g * kernel->matrix[i][j];
				avg_b += img->pixels[pos_i].b * kernel->matrix[i][j];
			}
		}
	pos_i = (y * img->w) + x;
	new_img->pixels[pos_i].r = (uint8_t)(avg_r / divider);
	new_img->pixels[pos_i].g = (uint8_t)(avg_g / divider);
	new_img->pixels[pos_i].b = (uint8_t)(avg_b / divider);
}
