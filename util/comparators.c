#include <stdio.h>

int compare_int(const void *item1, const void *item2)
{
	const long int i1 = *((long int *)item1);
	const long int i2 = *((long int *)item2);

	if (i1 == i2)
		return 0;

	return i1 > i2 ? 1 : -1;
}