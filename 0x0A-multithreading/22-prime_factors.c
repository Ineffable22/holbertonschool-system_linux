#include "multithreading.h"
static pthread_mutex_t mutex;

/**
 * mutex_init - initializes global mutex for printf buffer before main
 */
void mutex_init(void)
{
	pthread_mutex_init(&mutex, NULL);
}


/**
 * mutex_destroy - destroys global mutex for printf buffer after main
 */
void mutex_destroy(void)
{
	pthread_mutex_destroy(&mutex);
}

/**
 * create_task - Create and prepare data.
 * @entry: Is a pointer to the entry function of the task
 * @param: Is the parameter that will later be passed to the entry function
 *
 * Return: A pointer to the created task structure
 */
task_t *create_task(task_entry_t entry, void *param)
{
	task_t *task = NULL;

	if (!entry)
		return (NULL);
	task = malloc(sizeof(task_t));
	if (task == NULL)
	{
		fprintf(stderr, "Can not malloc\n");
		return (NULL);
	}
	task->entry = entry;
	task->status = PENDING;
	task->param = param;
	task->result = NULL;
	task->lock = mutex;
	return (task);
}

/**
 * destroy_task - Delete a task
 * @task: Is a pointer to the task to destroy
 *
 * Return: Nothing
 */
void destroy_task(task_t *task)
{
	if (!task)
		return;
	if (task->result)
	{
		list_destroy(task->result, free);
		free(task->result);
	}
	free(task);
}

/**
 * exec_tasks - Execute tasks from different nodes
 * @tasks: Is a pointer to the list of tasks to be executed
 *
 * Return: Nothing
 */
void *exec_tasks(list_t const *tasks)
{
	node_t *node = tasks->head;
	task_t *task = NULL;
	size_t i = 0;

	for (; i < tasks->size; i++, node = node->next)
	{
		task = node->content;
		pthread_mutex_lock(&mutex);
		if (task->status == PENDING)
		{
			task->status = STARTED;
			pthread_mutex_unlock(&mutex);
			tprintf("[%02lu] Started\n", i);
			task->result = task->entry(task->param);
			if (task->result)
			{
				task->status = SUCCESS;
				tprintf("[%02lu] Success\n", i);
			}
			else
			{
				task->status = FAILURE;
				tprintf("[%02lu] Failure\n", i);
			}
		}
		else
			pthread_mutex_unlock(&mutex);
	}
	return ((void *)tasks);
}
