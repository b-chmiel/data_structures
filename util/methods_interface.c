#include <stdlib.h>
#include "methods_interface.h"
#include "comparators.h"
#include "hash.h"

static int (*init_comparator(int (*compare)(
	const void *item1, const void *item2)))(const void *item1,
						const void *item2)
{
	int (*result)(const void *item1, const void *item2) = compare;

	if (result == NULL)
		result = compare_int;

	return result;
}

static void (*init_free(void (*free_el)(void *item)))(void *item)
{
	void (*result)(void *item) = free_el;

	if (free_el == NULL)
		result = free;

	return result;
}

static unsigned int (*init_hash(unsigned int (*hash)(const void *item)))(
	const void *item)
{
	unsigned int (*result)(const void *item) = hash;

	if (hash == NULL)
		result = hash_string;

	return result;
}

struct methods_interface *
init_methods_interface(int (*compare)(const void *item1, const void *item2),
		       void (*free_el)(void *item),
		       unsigned int (*hash)(const void *item))
{
	struct methods_interface *interface;
	interface = malloc(sizeof(struct methods_interface));
	interface->compare = init_comparator(compare);
	interface->free_element = init_free(free_el);
	interface->hash = init_hash(hash);

	return interface;
}
