#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash_set.h"
#include "hash.h"
#include "methods_interface.h"

struct hash_set *hash_set_init(struct methods_interface *interface, int size)
{
	struct hash_set *result = malloc(sizeof(struct hash_set));
	result->entries = malloc(sizeof(struct hash_set_entry) * size);
	result->size = size;
	result->interface = interface;

	for (int i = 0; i < size; i++) {
		result->entries[i] = NULL;
	}

	return result;
}

void hash_set_insert(struct hash_set **set, const char *key)
{
	if (key == NULL) {
		return;
	}

	int index = (*set)->interface->hash(key) % (*set)->size;
	struct hash_set_entry *to_insert =
		malloc(sizeof(struct hash_set_entry));
	to_insert->key = malloc(sizeof(key));
	strcpy(to_insert->key, key);
	to_insert->next = NULL;

	if ((*set)->entries[index] == NULL) {
		(*set)->entries[index] = to_insert;
		return;
	}

	struct hash_set_entry *tmp = (*set)->entries[index];

	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	tmp->next = to_insert;
}

bool hash_set_contains(struct hash_set *set, const char *key)
{
	int index = set->interface->hash(key) % set->size;

	if (set->entries[index] == NULL) {
		return false;
	}

	if (strcmp(set->entries[index]->key, key) == 0) {
		return true;
	}

	struct hash_set_entry *tmp = set->entries[index];

	while (tmp->next != NULL) {
		if (strcmp(tmp->next->key, key) == 0)
			return true;

		tmp = tmp->next;
	}

	return false;
}

void hash_set_free(struct hash_set *set)
{
	struct hash_set_entry *tmp;
	struct hash_set_entry *head;

	for (int i = 0; i < set->size; i++) {
		head = set->entries[i];

		while (head != NULL) {
			tmp = head;
			head = head->next;
			free(tmp->key);
			free(tmp);
		}
	}

	free(set->entries);
	free(set->interface);
	free(set);
}