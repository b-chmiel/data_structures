#include "methods_interface.h"

struct binary_tree {
	struct binary_tree_node *root;
	struct methods_interface *interface;
};

struct binary_tree_node {
	void *data;
	struct binary_tree_node *left;
	struct binary_tree_node *right;
};

struct binary_tree *binary_tree_init(struct methods_interface *interface);

void binary_tree_add(struct binary_tree **tree, void *data);

void binary_tree_add_at(struct binary_tree **tree, int index, void *data);

void *binary_tree_get_at(struct binary_tree *tree, int index);

void binary_tree_free(struct binary_tree *tree);

void binary_tree_clear(struct binary_tree **tree);

void binary_tree_print(struct binary_tree *tree);