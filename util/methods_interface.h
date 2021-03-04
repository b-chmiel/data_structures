#ifndef METHODS_INTERFACE_DEF
#define METHODS_INTERFACE_DEF

struct methods_interface {
	int (*compare)(const void *item_1, const void *item_2);
	void (*free_element)(void *item);
	unsigned int (*hash)(const void *item);
};

struct methods_interface *
init_methods_interface(int (*compare)(const void *item1, const void *item2),
		       void (*free_el)(void *item),
		       unsigned int (*hash)(const void *item));

#endif
