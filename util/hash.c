#include <string.h>

unsigned int hash_string(const void *key)
{
	const char *key_str = (char *)key;
	const int key_len = strlen(key_str);
	int sum = 0;

	for (int i = 0; i < key_len; i++)
		sum += key_str[i];

	return sum;
}