#include <malloc.h>
#include "binary_tree.h"

struct binary_tree *binary_tree_init(struct methods_interface *interface)
{
	struct binary_tree *result = malloc(sizeof(struct binary_tree));
	result->interface = interface;
	result->root = NULL;

	return result;
}