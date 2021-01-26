struct methods_interface {
	int (*compare) (void *item_1, void *item_2);
	void (*free_element) (void **item);
};