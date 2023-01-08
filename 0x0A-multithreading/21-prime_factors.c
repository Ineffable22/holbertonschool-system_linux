#include "multithreading.h"

/**
 * prime_factors - Factorizes a number into a list of prime factors.
 * @s:             Is the string representation of the number to factorize.
 *
 * Return:         Pointer to number
 */
list_t *prime_factors(char const *s)
{
	list_t *factors;
	unsigned long number = 0;
	unsigned long n = 2;
	unsigned long *divider = NULL;

	factors = malloc(sizeof(list_t));
	if (!factors)
	{
		fprintf(stderr, "Can not malloc\n");
		list_destroy(factors, free);
		free(factors);
		return (NULL);
	}
	list_init(factors);
	for (number = strtoul(s, NULL, 10); number % 2 == 0; number /= 2)
	{
		divider = malloc(sizeof(unsigned long));
		*divider = n;
		list_add(factors, divider);
	}
	for (n += 1; n * n <= number; n += 2)
	{
		for (; number % n == 0; number /= n)
		{
			divider = malloc(sizeof(unsigned long));
			*divider = n;
			list_add(factors, divider);
		}
	}
	if (number > 2)
	{
		divider = malloc(sizeof(unsigned long));
		*divider = number;
		list_add(factors, divider);
	}
	return (factors);
}
