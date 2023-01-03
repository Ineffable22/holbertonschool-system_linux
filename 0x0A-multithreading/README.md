# 0x0A-multithreading

# Files

### 0. Thread entry point
### [0-thread_entry.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0A-multithreading/0-thread_entry.c)

```C
#include <stddef.h>
#include <stdint.h>

/**
 * struct pixel_s - RGB pixel
 *
 * @r: Red component
 * @g: Green component
 * @b: Blue component
 */
typedef struct pixel_s
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel_t;

/**
 * struct img_s - Image
 *
 * @w:      Image width
 * @h:      Image height
 * @pixels: Array of pixels
 */
typedef struct img_s
{
    size_t w;
    size_t h;
    pixel_t *pixels;
} img_t;

/**
 * struct kernel_s - Convolution kernel
 *
 * @size:   Size of the matrix (both width and height)
 * @matrix: Kernel matrix
 */
typedef struct kernel_s
{
    size_t size;
    float **matrix;
} kernel_t;

/**
 * struct blur_portion_s - Information needed to blur a portion of an image
 *
 * @img:      Source image
 * @img_blur: Destination image
 * @x:        X position of the portion in the image
 * @y:        Y position of the portion in the image
 * @w:        Width of the portion
 * @h:        Height of the portion
 * @kernel:   Convolution kernel to use
 */
typedef struct blur_portion_s
{
    img_t const *img;
    img_t *img_blur;
    size_t x;
    size_t y;
    size_t w;
    size_t h;
    kernel_t const *kernel;
} blur_portion_t;

```

### 1. Thread Logger
### [1-tprintf.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0A-multithreading/1-tprintf.c)

```C
alex@~/0x0A-multithreading$ cat 0-main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, &thread_entry, "Holberton School");

    sleep(1);
    printf("Created thread ID -> %lu\n", tid);

    thread_entry("C is fun");
    printf("Should not be printed\n");
    return (EXIT_SUCCESS);
}
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 0-main.c 0-thread_entry.c -o 0-thread_entry -pthread
alex@~/0x0A-multithreading$ ./0-thread_entry
Holberton School
Created thread ID -> 139851772159744
C is fun
alex@~/0x0A-multithreading$

```

### 2. Blur portion of an image
### [10-blur_portion.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0A-multithreading/10-blur_portion.c)

```C
alex@~/0x0A-multithreading$ cat 1-main.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * _thread_entry - Thread entry point. Prints out a string
 *
 * @arg: Unused
 *
 * Return: NULL
 */
void *_thread_entry(__attribute__((unused))void *arg)
{
    tprintf("Hello from thread\n");
    return (NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, &_thread_entry, NULL);
    pthread_join(tid, NULL);

    tprintf("Hello from main thread\n");

    return (EXIT_SUCCESS);
}
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 1-main.c 1-tprintf.c -o 1-tprintf -pthread
alex@~/0x0A-multithreading$ ./1-tprintf
[140095003338496] Hello from thread
[140095011714880] Hello from main thread
alex@~/0x0A-multithreading$ ./1-tprintf
[139794647717632] Hello from thread
[139794656094016] Hello from main thread
alex@~/0x0A-multithreading$

```

### 3. Blur entire image
### [11-blur_image.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0A-multithreading/11-blur_image.c)

```C
alex@~/0x0A-multithreading$ cat 10-main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multithreading.h"

/**
 * load_kernel - Load convolution kernel from a file
 *
 * @kernel: Pointer to the kernel structure to fill in
 * @file:   Path to the file to parse
 */
void load_kernel(kernel_t *kernel, char const *file)
{
    FILE *f;
    size_t i, j;

    f = fopen(file, "r");
    fscanf(f, "%lu\n", &kernel->size);
    printf("Kernel size -> %lu\n", kernel->size);
    kernel->matrix = malloc(kernel->size * sizeof(float *));
    for (i = 0; i < kernel->size; i++)
    {
        kernel->matrix[i] = malloc(kernel->size * sizeof(float));
        for (j = 0; j < kernel->size; j++)
            fscanf(f, "%f", &kernel->matrix[i][j]);
    }
    fclose(f);
}

/**
 * load_image - Load an image from a PBM file
 *
 * @img:  Pointer to the image structure to fill in
 * @file: Path to the file to parse
 */
void load_image(img_t *img, char const *file)
{
    FILE *f;
    size_t i;

    f = fopen(file, "r");
    fscanf(f, "P6\n %lu %lu 255\n", &img->w, &img->h);
    printf("Image size -> %lu * %lu\n", img->w, img->h);
    img->pixels = malloc(img->w * img->h * sizeof(*img->pixels));

    for (i = 0; i < img->w * img->h; i++)
        fscanf(f, "%c%c%c", &img->pixels[i].r, &img->pixels[i].g, &img->pixels[i].b);
    fclose(f);
}

/**
 * img_copy - Copy an image structure
 *
 * @dest: Pointer to the image structure to fill in
 * @src:  Pointer to the image structure to copy
 */
void img_copy(img_t *dest, img_t const *src)
{
    size_t nb_pixels = src->w * src->h;

    dest->w = src->w;
    dest->h = src->h;
    dest->pixels = malloc(nb_pixels * sizeof(pixel_t));
    memcpy(dest->pixels, src->pixels, nb_pixels * sizeof(pixel_t));
}

/**
 * write_image - Write an image into a PBM file
 *
 * @img:  Pointer to the image structure to write into a file
 * @file: Path to the file to write the image into
 */
void write_image(img_t const *img, char const *file)
{
    FILE *f;
    size_t i;

    f = fopen(file, "w");
    fprintf(f, "P6\n %lu %lu 255\n", img->w, img->h);
    for (i = 0; i < img->w * img->h; i++)
        fprintf(f, "%c%c%c", img->pixels[i].r, img->pixels[i].g, img->pixels[i].b);
    fclose(f);
}

/**
 * main - Entry point
 *
 * @ac: Arguments counter
 * @av: Arguments vector
 *
 * Return: EXIT_SUCCESS upon success, error code upon failure
 */
int main(int ac, char **av)
{
    img_t img, img_blur;
    kernel_t kernel;
    blur_portion_t portion;
    size_t i;

    if (ac < 3)
    {
        printf("Usage: %s image.ppm kernel.knl\n", av[0]);
        return (EXIT_FAILURE);
    }

    load_image(&img, av[1]);
    img_copy(&img_blur, &img);
    load_kernel(&kernel, av[2]);

    /* Execute blur */
    portion.img = &img;
    portion.img_blur = &img_blur;
    portion.kernel = &kernel;
    portion.w = img.w / 2;
    portion.h = img.h / 2;
    portion.x = img.w / 4;
    portion.y = img.h / 4;
    blur_portion(&portion);

    write_image(&img_blur, "output.pbm");

    /* Cleanup */
    free(img.pixels);
    free(img_blur.pixels);
    for (i = 0; i < kernel.size; i++)
        free(kernel.matrix[i]);
    free(kernel.matrix);

    return (EXIT_SUCCESS);
}
alex@~/0x0A-multithreading$ cat images/kernel_0.knl
5
0.1 0.25 0.5 0.25 0.1
0.25 0.5 0.85 0.5 0.25
0.5 0.85 1.0 0.85 0.5
0.25 0.5 0.85 0.5 0.25
0.1 0.25 0.5 0.25 0.1
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 10-main.c 10-blur_portion.c -o 10-blur_portion
alex@~/0x0A-multithreading$ ./10-blur_portion images/car.pbm images/kernel_0.knl
Image size -> 960 * 540
Kernel size -> 5
alex@~/0x0A-multithreading$

```

### 4. Thread logger v2
### [20-tprintf.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0A-multithreading/20-tprintf.c)

```C
alex@~/0x0A-multithreading$ cat 11-main.c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "multithreading.h"

/**
 * load_kernel - Load convolution kernel from a file
 *
 * @kernel: Pointer to the kernel structure to fill in
 * @file:   Path to the file to parse
 */
void load_kernel(kernel_t *kernel, char const *file)
{
    FILE *f;
    size_t i, j;

    f = fopen(file, "r");
    fscanf(f, "%lu\n", &kernel->size);
    printf("Kernel size -> %lu\n", kernel->size);
    kernel->matrix = malloc(kernel->size * sizeof(float *));
    for (i = 0; i < kernel->size; i++)
    {
        kernel->matrix[i] = malloc(kernel->size * sizeof(float));
        for (j = 0; j < kernel->size; j++)
            fscanf(f, "%f", &kernel->matrix[i][j]);
    }
    fclose(f);
}

/**
 * load_image - Load an image from a PBM file
 *
 * @img:  Pointer to the image structure to fill in
 * @file: Path to the file to parse
 */
void load_image(img_t *img, char const *file)
{
    FILE *f;
    size_t i;

    f = fopen(file, "r");
    fscanf(f, "P6\n %lu %lu 255\n", &img->w, &img->h);
    printf("Image size -> %lu * %lu\n", img->w, img->h);
    img->pixels = malloc(img->w * img->h * sizeof(*img->pixels));

    for (i = 0; i < img->w * img->h; i++)
        fscanf(f, "%c%c%c", &img->pixels[i].r, &img->pixels[i].g, &img->pixels[i].b);
    fclose(f);
}

/**
 * img_copy - Copy an image structure
 *
 * @dest: Pointer to the image structure to fill in
 * @src:  Pointer to the image structure to copy
 */
void img_copy(img_t *dest, img_t const *src)
{
    size_t nb_pixels = src->w * src->h;

    dest->w = src->w;
    dest->h = src->h;
    dest->pixels = malloc(nb_pixels * sizeof(pixel_t));
    memcpy(dest->pixels, src->pixels, nb_pixels * sizeof(pixel_t));
}

/**
 * write_image - Write an image into a PBM file
 *
 * @img:  Pointer to the image structure to write into a file
 * @file: Path to the file to write the image into
 */
void write_image(img_t const *img, char const *file)
{
    FILE *f;
    size_t i;

    f = fopen(file, "w");
    fprintf(f, "P6\n %lu %lu 255\n", img->w, img->h);
    for (i = 0; i < img->w * img->h; i++)
        fprintf(f, "%c%c%c", img->pixels[i].r, img->pixels[i].g, img->pixels[i].b);
    fclose(f);
}

/**
 * main - Entry point
 *
 * @ac: Arguments counter
 * @av: Arguments vector
 *
 * Return: EXIT_SUCCESS upon success, error code upon failure
 */
int main(int ac, char **av)
{
    img_t img;
    img_t img_blur;
    kernel_t kernel;
    size_t i;

    if (ac < 3)
    {
        printf("Usage: %s image.ppm kernel.knl\n", av[0]);
        return (EXIT_FAILURE);
    }

    load_image(&img, av[1]);
    img_copy(&img_blur, &img);
    load_kernel(&kernel, av[2]);

    /* Execute blur */
    blur_image(&img_blur, &img, &kernel);

    write_image(&img_blur, "output.pbm");

    /* Cleanup */
    free(img.pixels);
    free(img_blur.pixels);
    for (i = 0; i < kernel.size; i++)
        free(kernel.matrix[i]);
    free(kernel.matrix);

    return (EXIT_SUCCESS);
}
alex@~/0x0A-multithreading$ cat images/kernel_0.knl
5
0.1 0.25 0.5 0.25 0.1
0.25 0.5 0.85 0.5 0.25
0.5 0.85 1.0 0.85 0.5
0.25 0.5 0.85 0.5 0.25
0.1 0.25 0.5 0.25 0.1
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 11-main.c 11-blur_image.c 10-blur_portion.c -o 11-blur_image -pthread
alex@~/0x0A-multithreading$ time ./11-blur_image images/car.pbm images/kernel_0.knl
Image size -> 960 * 540
Kernel size -> 5

real    0m0.143s
user    0m0.197s
sys 0m0.076s
alex@~/0x0A-multithreading$

```

### 5. Number to prime factors
### [21-prime_factors.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0A-multithreading/21-prime_factors.c)

```C
alex@~/0x0A-multithreading$ cat 20-main.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

#define NB_THREADS  10

/**
 * _thread_entry - Thread entry point. Prints out a string
 *
 * @arg: Unused
 *
 * Return: NULL
 */
void *_thread_entry(__attribute__((unused))void *arg)
{
    tprintf("Hello from thread\n");
    return (NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
    pthread_t tid[NB_THREADS];
    int i;

    for (i = 0; i < NB_THREADS; i++)
        pthread_create(&tid[i], NULL, &_thread_entry, NULL);

    tprintf("Hello from main thread\n");

    for (i = 0; i < NB_THREADS; i++)
        pthread_join(tid[i], NULL);

    return (EXIT_SUCCESS);
}
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 20-main.c 1-tprintf.c -o 20-tprintf -pthread
alex@~/0x0A-multithreading$ ./20-tprintf
[139996670035712] [139996678428416] [139996686821120] [139996695197504] Hello from thread
[139996644857600] Hello from thread
[139996628072192] Hello from thread
[139996619679488] Hello from thread
Hello from main thread
Hello from thread
Hello from thread
[139996611286784] Hello from thread
[139996661643008] Hello from thread
[139996636464896] Hello from thread
[139996653250304] Hello from thread
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 20-main.c 20-tprintf.c -o 20-tprintf -pthread
alex@~/0x0A-multithreading$ ./20-tprintf
[140146877490944] Hello from thread
[140146852312832] Hello from thread
[140146843920128] Hello from thread
[140146860705536] Hello from thread
[140146835527424] Hello from thread
[140146869098240] Hello from thread
[140146818742016] Hello from thread
[140146885867328] Hello from main thread
[140146810349312] Hello from thread
[140146801956608] Hello from thread
[140146827134720] Hello from thread
alex@~/0x0A-multithreading$

```

### 6. Number to prime factors v2
### [22-prime_factors.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0A-multithreading/22-prime_factors.c)

```C
alex@~/0x0A-multithreading$ cat 21-main.c
#include <stdlib.h>
#include <stdio.h>
#include "multithreading.h"

/**
 * print_factors - Print a nmber and its prime factorization
 *
 * @s:       Number as string
 * @factors: List of prime factors
 */
static void print_factors(char const *s, list_t const *factors)
{
    node_t const *factor;

    printf("%s =", s);
    for (factor = factors->head; factor; factor = factor->next)
    {
        unsigned long n = *((unsigned long *)factor->content);

        printf("%s %lu", factor->prev ? " *" : "", n);
    }
    printf("\n");
}

/**
 * main - Entry point
 *
 * @ac: Arguments count
 * @av: Arguments vector
 *
 * Return: EXIT_SUCCESS upon success, EXIT_FAILURE otherwise
 */
int main(int ac, char **av)
{
    size_t i;

    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s n\n", av[0]);
        return (EXIT_FAILURE);
    }

    for (i = 1; i < (size_t)ac; i++)
    {
        list_t *factors;

        factors = prime_factors(av[i]);
        print_factors(av[i], factors);
        list_destroy(factors, free);
        free(factors);
    }

    return (EXIT_SUCCESS);
}
alex@~/0x0A-multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 21-main.c 21-prime_factors.c list.c -o 21-prime_factors
alex@~/0x0A-multithreading$ ./21-prime_factors 745 872346 79283472974
745 = 5 * 149
872346 = 2 * 3 * 145391
79283472974 = 2 * 757 * 52366891
alex@~/0x0A-multithreading$ ./21-prime_factors 1048576
1048576 = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
alex@~/0x0A-multithreading$ ./21-prime_factors 18446744073709551612 18446744073709551609 18446744073709551608
18446744073709551612 = 2 * 2 * 3 * 715827883 * 2147483647
18446744073709551609 = 3 * 3 * 818923289 * 2502845209
18446744073709551608 = 2 * 2 * 2 * 2305843009213693951
alex@~/0x0A-multithreading$

```

