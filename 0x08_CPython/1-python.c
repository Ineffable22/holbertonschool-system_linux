#include <Python.h>
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
	int i = 0;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %lu\n", Py_SIZE(p));
	printf("[*] Allocated = %lu\n", ((PyListObject *)p)->allocated);
	for (i = 0; i < Py_SIZE(p); i++)
		printf("Element %d: %s\n", i, Py_TYPE(PyList_GetItem(p, i))
		       ->tp_name);
}
