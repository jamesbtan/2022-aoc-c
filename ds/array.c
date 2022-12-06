#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t gcd(size_t a, size_t b) {
	while (a != 0) {
		b %= a;
		size_t tmp = a;
		a = b;
		b = tmp;
	}
	return b;
}
// rotate leftwards
void rotate(void *ptr, size_t count, size_t size, size_t rot)
{
	if (count == 0) return;
	rot %= count;
	if (rot == 0) return;
	uint8_t *bptr = ptr;
	uint8_t buf[size];
	size_t cyc = gcd(count, rot);
	for (size_t i = 0; i < cyc; i++) {
		size_t j = i;
		for (size_t s = 0; s < size; s++) {
			buf[s] = bptr[j * size + s];
		}
		while (1) {
			size_t k = (j + rot) % count;
			if (k == i) break;
			for (size_t s = 0; s < size; s++) {
				bptr[j * size + s] = bptr[k * size + s];
			}
			j = k;
		}
		for (size_t s = 0; s < size; s++) {
			bptr[j * size + s] = buf[s];
		}
	}
}
void heapify(
	void *ptr,
	size_t count,
	size_t size,
	int (*comp)(const void *, const void *))
{
}
void insert_heap(
	const void *item,
	void *ptr,
	size_t count,
	size_t size,
	int (*comp)(const void *, const void *))
{
}
