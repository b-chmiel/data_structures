#include <check.h>

void single_linked_list_setup(void);
void single_linked_list_teardown(void);
void binary_tree_setup(void);
void binary_tree_teardown(void);
void stack_setup(void);
void stack_teardown(void);
void btree_setup(void);
void btree_teardown(void);

Suite *binary_tree_suite(void);
Suite *single_linked_list_suite(void);
Suite *stack_suite(void);
Suite *btree_suite(void);