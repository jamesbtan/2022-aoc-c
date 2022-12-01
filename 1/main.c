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
	int ctot = 0;
	char buf[10];
	while (fgets(buf, 10, fp) != NULL) {
		if (strlen(buf) == 1) {
			maxes[NUM-1] = ctot;
			ctot = 0;
			qsort(maxes, NUM, sizeof(int), comp);
			for (int i = 0; i < NUM; i++) {
				if (i != 0) {
					printf(" ");
				}
				printf("%d", maxes[i]);
			}
			printf("\n");
		} else {
			int curr = strtol(buf, NULL, 10);
			ctot += curr;
		}
	}

	printf("\n");
	ctot = 0;
	for (int i = 0; i < NUM - 1; i++) {
		if (i != 0) {
			printf(" ");
		}
		printf("%d", maxes[i]);
		ctot += maxes[i];
	}
	printf("\n%d\n", ctot);
}
