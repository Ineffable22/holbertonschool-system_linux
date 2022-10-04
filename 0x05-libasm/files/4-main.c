#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  "School"
#define S3  "Socool"
#define S4  ""
#define S5  "Holberton"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	assert(strstr(S1, S1) == asm_strstr(S1, S1));
	assert(strstr(S1, S2) == asm_strstr(S1, S2));
	assert(strstr(S1, S3) == asm_strstr(S1, S3));
	assert(strstr(S1, S4) == asm_strstr(S1, S4));
	assert(strstr(S1, S5) == asm_strstr(S1, S5));

	assert(strstr(S2, S1) == asm_strstr(S2, S1));
	assert(strstr(S2, S2) == asm_strstr(S2, S2));
	assert(strstr(S2, S3) == asm_strstr(S2, S3));
	assert(strstr(S2, S4) == asm_strstr(S2, S4));
	assert(strstr(S2, S5) == asm_strstr(S2, S5));

	assert(strstr(S3, S1) == asm_strstr(S3, S1));
	assert(strstr(S3, S2) == asm_strstr(S3, S2));
	assert(strstr(S3, S3) == asm_strstr(S3, S3));
	assert(strstr(S3, S4) == asm_strstr(S3, S4));
	assert(strstr(S3, S5) == asm_strstr(S3, S5));

	assert(strstr(S4, S1) == asm_strstr(S4, S1));
	assert(strstr(S4, S2) == asm_strstr(S4, S2));
	assert(strstr(S4, S3) == asm_strstr(S4, S3));
	assert(strstr(S4, S4) == asm_strstr(S4, S4));
	assert(strstr(S4, S5) == asm_strstr(S4, S5));

	assert(strstr(S5, S1) == asm_strstr(S5, S1));
	assert(strstr(S5, S2) == asm_strstr(S5, S2));
	assert(strstr(S5, S3) == asm_strstr(S5, S3));
	assert(strstr(S5, S4) == asm_strstr(S5, S4));
	assert(strstr(S5, S5) == asm_strstr(S5, S5));

	printf("All good!\n");
	return (EXIT_SUCCESS);
}
