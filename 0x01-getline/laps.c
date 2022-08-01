#include "laps.h"

/**
 * sort - Sorting list
 * @cars: array with all cars
 * @len: array cars length
 * @id: value to add in sort
 *
 * Return: Array with new car.
 */
int **sort(int **cars, size_t len, int id)
{
	size_t i = 0;
	int tmp_id1 = id, tmp1 = 0, tmp_id2 = 0, tmp2 = 0;
	size_t ss = (len == 0) ? 1 : len + 2;

	cars[0] = realloc(cars[0], sizeof(int) * ss);
	cars[1] = realloc(cars[1], sizeof(int) * ss);

	printf("Car %d joined the race\n", id);
	if (len == 0)
	{
		cars[0][len] = id;
		cars[1][len] = 0;
	}
	for (i = 0; i < len && id > cars[0][i]; i++)
	{}
	if (i == len)
	{
		cars[0][len] = id;
		cars[1][len] = 0;
	}
	else
	{
		while (i <= len)
		{
			tmp_id2 = tmp_id1;
			tmp2 = tmp1;
			tmp_id1 = cars[0][i];
			tmp1 = cars[1][i];
			cars[0][i] = tmp_id2;
			cars[1][i] = tmp2;
			tmp_id2 = cars[0][i + 1];
			tmp2 = cars[1][i + 1];
			i++;
		}

	}
	return (cars);
}

/**
 * race_state - Keeps track of the number of laps made by several
 * cars in a race
 * @id: is an array of int representing the “identifier” of each car.
 * @size: is the size of this array
 *
 * Return: Nothing
 */
void race_state(int *id, size_t size)
{
	static int **cars;
	static size_t len;
	size_t i = 0, j = 0, length = len, bol = 0;

	if (!cars)
	{
		cars = NULL;
		cars = malloc(sizeof(int *) * 2);
		cars[0] = NULL, cars[1] = NULL;
	}

	if (size == 0 && cars)
	{
		free(cars[0]), free(cars[1]), free(cars);
		return;
	}
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < length; j++)
		{
			if (cars[0][j] == id[i])
			{
				bol = 1;
				break;
			}
		}
		if (bol == 0)
		{
			cars = sort(cars, len, id[i]);
			len++;
		}
		else
			cars[1][j] += 1;
		bol = 0;
	}
	printf("Race state:\n");
	for (i = 0; i < len; i++)
		printf("Car %d [%d laps]\n", cars[0][i], cars[1][i]);
}
