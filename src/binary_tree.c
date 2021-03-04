#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include "binary_tree.h"
#include "comparators.h"
#include "single_linked_list.h"

struct binary_tree *binary_tree_init(struct methods_interface *interface,
				     size_t size)
{
	struct binary_tree *result = malloc(sizeof(struct binary_tree));
	result->interface = interface;
	result->root = NULL;
	result->size = size;
	result->el_cnt = 0;

	return result;
}

static struct binary_tree_node *
init_binary_tree_node(void *data, struct binary_tree_node *left,
		      struct binary_tree_node *right)
{
	struct binary_tree_node *result =
		malloc(sizeof(struct binary_tree_node));
	result->data = data;
	result->left = left;
	result->right = right;

	return result;
}

bool insert_node_to_left(struct binary_tree_node **current,
			 struct binary_tree_node *to_insert, int *el_cnt)
{
	if ((*current)->left != NULL) {
		*current = (*current)->left;
		return false;
	} else {
		(*current)->left = to_insert;
		(*el_cnt)++;
		return true;
	}
}

bool insert_node_to_right(struct binary_tree_node **current,
			  struct binary_tree_node *to_insert, int *el_cnt)
{
	if ((*current)->right != NULL) {
		*current = (*current)->right;
		return false;
	} else {
		(*current)->right = to_insert;
		(*el_cnt)++;
		return true;
	}
}

bool binary_tree_add(struct binary_tree **tree, void *data)
{
	int *el_cnt = &(*tree)->el_cnt;
	struct binary_tree_node *current = (*tree)->root;
	struct binary_tree_node **root = &(*tree)->root;
	struct binary_tree_node *to_insert =
		init_binary_tree_node(data, NULL, NULL);

	int (*compare)(const void *, const void *) =
		(*tree)->interface->compare;

	if (current == NULL) {
		*root = to_insert;
		(*el_cnt)++;
		return true;
	}

	int cmp_result;
	while (current != NULL) {
		cmp_result = compare(&data, &(current->data));

		if (cmp_result == 0) {
			return false;
		} else if (cmp_result < 0) {
			if (insert_node_to_left(&current, to_insert, el_cnt))
				return true;
		} else {
			if (insert_node_to_right(&current, to_insert, el_cnt))
				return true;
		}
	}

	return false;
}

static void clear_rec(struct binary_tree_node *node,
		      void (*free_element)(void *item))
{
	if (node == NULL)
		return;

	clear_rec(node->left, free_element);
	clear_rec(node->right, free_element);

	free_element(node);
	node = NULL;
}

void binary_tree_clear(struct binary_tree **tree)
{
	struct binary_tree_node **root = &(*tree)->root;
	void (*free_element)(void *item) = (*tree)->interface->free_element;
	clear_rec(*root, free_element);
}

void binary_tree_free(struct binary_tree *tree)
{
	binary_tree_clear(&tree);
	free(tree->interface);
	free(tree);
}

static void dfs_inorder_rec(struct binary_tree_node *node,
			    struct single_linked_list **result)
{
	if (node == NULL)
		return;

	single_linked_list_add(result, node->data);
	dfs_inorder_rec(node->left, result);
	dfs_inorder_rec(node->right, result);
}

void binary_tree_dfs_inorder(struct binary_tree *tree,
			     struct single_linked_list **result)
{
	dfs_inorder_rec(tree->root, result);
}

static void dfs_preorder_rec(struct binary_tree_node *node,
			     struct single_linked_list **result)
{
	if (node == NULL)
		return;

	dfs_preorder_rec(node->left, result);
	single_linked_list_add(result, node->data);
	dfs_preorder_rec(node->right, result);
}

void binary_tree_dfs_preorder(struct binary_tree *tree,
			      struct single_linked_list **result)
{
	dfs_preorder_rec(tree->root, result);
}

static void dfs_postorder_rec(struct binary_tree_node *node,
			      struct single_linked_list **result)
{
	if (node == NULL)
		return;

	dfs_postorder_rec(node->left, result);
	dfs_postorder_rec(node->right, result);
	single_linked_list_add(result, node->data);
}

void binary_tree_dfs_postorder(struct binary_tree *tree,
			       struct single_linked_list **result)
{
	dfs_postorder_rec(tree->root, result);
}