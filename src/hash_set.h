#include <stdbool.h>
#include "methods_interface.h"

#ifndef HASH_SET_DEF
#define HASH_SET_DEF

struct hash_set_entry {
	char *key;
	struct hash_set_entry *next;
};

struct hash_set {
	struct hash_set_entry **entries;
	struct methods_interface *interface;
	int size;
};

struct hash_set *hash_set_init(struct methods_interface *interface, int size);

struct hash_set *hash_set_quick_init(char *words[], int number_of_args);

void hash_set_insert(struct hash_set **set, char *key);

bool hash_set_contains(struct hash_set *set, char *key);

void hash_set_free(struct hash_set *set);

#endif