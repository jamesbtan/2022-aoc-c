#include <stdio.h>

typedef struct {
	int s;
	int e;
} range;

int contains(range a, range b) {
	return a.s >= b.s && a.e <= b.e;
}

int intersect(range a, range b) {
	return a.s <= b.e && a.e >= b.s;
}

int main(void)
{
	FILE *fp = fopen("data/input4", "r");
	if (fp == NULL) {
		return 1;
	}
	int t = 0;
	range r1, r2;
	while (fscanf(fp, "%d-%d,%d-%d\n", &r1.s, &r1.e, &r2.s, &r2.e) != EOF) {
#ifdef PART1
		if (contains(r1, r2) || contains(r2, r1)) {
#else
		if (intersect(r1, r2)) {
#endif
			t++;
		}
	}
	fclose(fp);
	printf("%d\n", t);
}
