#include <stdlib.h>
#include "btree.h"

struct btree *btree_init(struct methods_interface *interface)
{
	struct btree *tree = malloc(sizeof(struct btree));
	tree->interface = interface;
	tree->root = NULL;

	return tree;
}

void btree_add(struct btree **tree, void *key, void *data)
{
	struct btree_data_node *to_insert =
		malloc(sizeof(struct btree_data_node));
	to_insert->data = data;
	to_insert->key = key;

	if ((*tree) == NULL) {
		return;
	}

	if ((*tree)->root == NULL) {
		struct btree_node *node = malloc(sizeof(struct btree_node));
		node->data_nodes = malloc(sizeof(struct btree_data_node));
		node->data_nodes[0] = to_insert;
		node->childrens = NULL;

		(*tree)->root = node;
		node->n_nodes = 1;
		return;
	}
}