#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "array_list.h"

/**
*	Reallocates the array_list data with the double amount of space
*	@param list the array_list to double the data at
*	@return 1 on success and -1 on failure
*/
static int array_list__realloc(struct array_list *list);

struct array_list *array_list_create(size_t data_size) {
	struct array_list *list = malloc(sizeof(struct array_list));
	if (!list) {
		return NULL;
	}
	list->data = malloc(data_size * DEFAULT_LENGTH);
	if (!list->data) {
		free(list);
		return NULL;
	}
	list->data_size = data_size;
	list->max_length = DEFAULT_LENGTH;
	list->length = 0;
	
	return list;
}

void array_list_free(struct array_list *list) {
	free(list->data);
	free(list);
	list = NULL;
}

int array_list_add(struct array_list *list, void *data) {	
	/* Check if it need to expand the array_list */
	if (list->length == list->max_length) {
		if (array_list__realloc(list) == -1) {
			return -1;
		}
	}
	/* Copy the data into the array list*/
	int offset = list->length * list->data_size;
	memcpy(list->data + offset, data, list->data_size);
	++(list->length);
	return 1;
}

int array_list_remove(struct array_list *list, int index) {
	/* Check if index is in bound */
	if (index < 0 || list->length == 0 || (size_t)index > list->length - 1) {
		return -1;
	}
	/* Removes the data at index index*/
	int offset = index * list->data_size;
	memcpy(list->data + offset, list->data + offset + list->data_size, list->length * list->data_size - offset);
	--(list->length);
	return -1;
}

int array_list_set(struct array_list *list, int index, void *data) {
	/* Check if index is in bound */
	if (index < 0 || list->length == 0 || (size_t)index > list->length - 1) {
		return -1;
	}
	/* Overwrite the data at index with the new data */
	int offset = index * list->data_size;
	memcpy(list->data + offset, data, list->data_size);
	return 1;
}

void *array_list_get(struct array_list *list, int index) {
	/* Check if index is in bound */
	if (index < 0 || list->length == 0 || (size_t)index > list->length - 1) {
		return NULL;
	}
	/* Return the data at index index */
	int offset = index * list->data_size;
	void *data = list->data + offset;
	return data;
}

static int array_list__realloc(struct array_list *list) {
	list->data = realloc(list->data, list->data_size * list->max_length * 2);
	if (!list->data) {
		return -1;
	}
	list->max_length *= 2;
	return 1;
}