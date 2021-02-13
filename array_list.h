#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <stddef.h>

#define DEFAULT_LENGTH 10

struct array_list {
	size_t data_size;		/* Size of each element */
	size_t max_length;		/* The total length of the current allocated memory */
	size_t length;			/* The total amouont of elements in the array */
	void *data;				/* Pointer to the array */
};

/**
* Creates an array_list structure and inizialised all the variables.
* @param data_size the size of each element in the array array_list->data
* @returns the array_list of success and NULL on failure
*/
struct array_list *array_list_create(size_t data_size);
/**
* Cleans up an array_list and dealloctes all the memory
* @param list the array_list to clean up
* @note needs to be called to avoid memory leaks
*/
void array_list_free(struct array_list *list);
/**
* Adds an elemnt to the end of an array_list
* @param list the array_list to add the element to
* @returns 1 on success and -1 on failure
*/
int array_list_add(struct array_list *list, void *data);
/**
* Removes an elemnt from an array_list
* @param list the array_list to remove the element from
* @param index the index of the elemnt that is removed
* @returns 1 on success and -1 on failure
*/
int array_list_remove(struct array_list *list, int index);
/**
* Sets an element of an array_list
* @param list the array_list to set an element
* @param index the index of the elemnt that is changed
* @returns 1 on success and -1 on failure
*/
int array_list_set(struct array_list *list, int index, void *data);
/**
* Returns an element of an array_list
* @param list the array_list to get an element from
* @param index the index of the elemnt that is changed
* @returns the element and NULL on failure
*/
void *array_list_get(struct array_list *list, int index);

#endif