void rotate(void *ptr, size_t count, size_t size, size_t rot);
void heapify(
	void *ptr,
	size_t count,
	size_t size,
	int (*comp)(const void *, const void *));
void insert_heap(
	const void *item,
	void *ptr,
	size_t count,
	size_t size,
	int (*comp)(const void *, const void *));
