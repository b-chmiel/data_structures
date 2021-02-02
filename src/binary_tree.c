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

bool binary_tree_add(struct binary_tree **tree, void *data)
{
	struct binary_tree_node *current = (*tree)->root;
	struct binary_tree_node *to_insert =
		malloc(sizeof(struct binary_tree_node));
	to_insert->data = data;
	to_insert->left = NULL;
	to_insert->right = NULL;

	int (*compare)(const void *, const void *) =
		(*tree)->interface->compare;

	if ((*tree)->interface->compare == NULL)
		compare = compare_int;

	if (current == NULL) {
		(*tree)->root = to_insert;
		(*tree)->el_cnt++;
		return true;
	}

	int cmp_result;
	while (current != NULL) {
		cmp_result = compare(&data, &(current->data));

		if (cmp_result == 0) {
			return false;
		} else if (cmp_result < 0) {
			if (current->left != NULL) {
				current = current->left;
			} else {
				current->left = to_insert;
				(*tree)->el_cnt++;
				return true;
			}
		} else {
			if (current->right != NULL) {
				current = current->right;
			} else {
				current->right = to_insert;
				(*tree)->el_cnt++;
				return true;
			}
		}
	}

	return false;
}

static void clear_rec(struct binary_tree_node *node,
		      void (*free_element)(void *item))
{
	if (node == NULL) {
		return;
	}

	clear_rec(node->left, free_element);
	clear_rec(node->right, free_element);

	free_element(node);
	node = NULL;
}

void binary_tree_clear(struct binary_tree **tree)
{
	clear_rec((*tree)->root, (*tree)->interface->free_element);
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
	if (node == NULL) {
		return;
	}

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
	if (node == NULL) {
		return;
	}

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
	if (node == NULL) {
		return;
	}

	dfs_postorder_rec(node->left, result);
	dfs_postorder_rec(node->right, result);
	single_linked_list_add(result, node->data);
}

void binary_tree_dfs_postorder(struct binary_tree *tree,
			       struct single_linked_list **result)
{
	dfs_postorder_rec(tree->root, result);
}