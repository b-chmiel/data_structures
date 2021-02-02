#ifndef METHODS_INTERFACE_DEF
#define METHODS_INTERFACE_DEF

struct methods_interface {
	int (*compare)(const void *item_1, const void *item_2);
	void (*free_element)(void *item);
};

#endif