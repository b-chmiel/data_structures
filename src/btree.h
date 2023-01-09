#ifndef BTREE_DEF
#define BTREE_DEF

#include "methods_interface.h"

#define BTREE_MAX_CHILD 4

struct btree {
	struct btree_node *root;
	struct methods_interface *interface;
};

struct btree_node {
	struct btree_node **childrens;
	struct btree_data_node **data_nodes;
	int n_nodes;
};

struct btree_data_node {
	void *key;
	void *data;
};

struct btree *btree_init(struct methods_interface *interface);

void btree_add(struct btree **tree, void *key, void *data);

void btree_remove(struct btree **tree, void *key);

void btree_get(struct btree *tree, void *key);

void btree_clear(struct btree **tree);

void btree_free(struct btree *tree);

static void btree_balance(struct btree **tree);

#endif