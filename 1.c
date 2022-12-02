#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// number to save
#ifdef PART1
#define NUM 1
#else
#define NUM 3
#endif

int main(void)
{
	FILE *fp = fopen("data/input1", "r");
	int maxes[NUM+1] = {0}; // add 1 to NUM as a buffer
	char buf[10];
	while (fgets(buf, 10, fp) != NULL) {
		if (strlen(buf) == 1) {
			for (int i = NUM; i > 0 && maxes[i-1] < maxes[i]; i--) {
				int tmp = maxes[i];
				maxes[i] = maxes[i-1];
				maxes[i-1] = tmp;
			}
			maxes[NUM] = 0;
		} else {
			int curr = strtol(buf, NULL, 10);
			maxes[NUM] += curr;
		}
	}
	fclose(fp);

	int tot = 0;
	for (int i = 0; i < NUM; i++) {
		tot += maxes[i];
	}
	printf("%d\n", tot);
}
