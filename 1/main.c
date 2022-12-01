#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int comp(const void *a, const void *b)
{
	int a_val = *(const int *)a;
	int b_val = *(const int *)b;
	return (b_val > a_val) - (a_val > b_val);
}

// number to save +1 as a buffer
// part 1
// #define NUM 2
// part 2
#define NUM 4

int main(void)
{
	FILE *fp = fopen("input", "r");
	int maxes[NUM] = {0};
	char buf[10];
	while (fgets(buf, 10, fp) != NULL) {
		if (strlen(buf) == 1) {
			qsort(maxes, NUM, sizeof(int), comp);
			for (int i = 0; i < NUM; i++) {
				if (i != 0) {
					printf(" ");
				}
				printf("%d", maxes[i]);
			}
			printf("\n");
			maxes[NUM-1] = 0;
		} else {
			int curr = strtol(buf, NULL, 10);
			maxes[NUM-1] += curr;
		}
	}

	printf("\n");
	int tot = 0;
	for (int i = 0; i < NUM - 1; i++) {
		if (i != 0) {
			printf(" ");
		}
		printf("%d", maxes[i]);
		tot += maxes[i];
	}
	printf("\n%d\n", tot);
}
