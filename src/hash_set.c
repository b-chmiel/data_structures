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

	for (int i = 0; i < size; i++)
		result->entries[i] = NULL;

	return result;
}

struct hash_set *hash_set_quick_init(char *words[], int number_of_args)
{
	if (words == NULL)
		return NULL;

	const int size = number_of_args * 2;
	struct hash_set *result;
	struct methods_interface *interface;

	interface = init_methods_interface(NULL, NULL, NULL);
	result = hash_set_init(interface, size);

	for (int i = 0; i < number_of_args; i++)
		hash_set_insert(&result, words[i]);

	return result;
}

static struct hash_set_entry *init_hash_set_entry(char *key)
{
	struct hash_set_entry *result = malloc(sizeof(struct hash_set_entry));
	size_t len = strlen(key);

	result->key = malloc((len + 1) * sizeof(char));
	strncpy(result->key, key, len);
	result->key[len] = '\0';
	result->next = NULL;

	return result;
}

void hash_set_insert(struct hash_set **set, char *key)
{
	if (key == NULL)
		return;

	int index = (*set)->interface->hash(key) % (*set)->size;
	struct hash_set_entry *to_insert = init_hash_set_entry(key);
	struct hash_set_entry *curr = (*set)->entries[index];

	if (curr == NULL) {
		(*set)->entries[index] = to_insert;
	} else {
		while (curr->next != NULL)
			curr = curr->next;

		curr->next = to_insert;
	}
}

bool hash_set_contains(struct hash_set *set, char *key)
{
	int index = set->interface->hash(key) % set->size;
	struct hash_set_entry *tmp = set->entries[index];

	if (tmp == NULL)
		return false;

	if (strcmp(tmp->key, key) == 0)
		return true;

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