#include <stdio.h>
#include <sys/types.h>
#include <object.h>
#include <listobject.h>

/**
 * print_python_list - Prints some basic info about Python lists.
 * @p: Pointer to Python object
 *
 * Return: Nothing
 */
void print_python_list(PyObject *p)
{
	int i = 0, size = PyList_Size(p);

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %d\n", size);
	printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);
	for (; i < size; i++)
		printf("Element %d: %s\n", i, Py_TYPE(PyList_GetItem(p, i))->tp_name);
}
