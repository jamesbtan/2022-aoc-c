#include <stdio.h>
#include <string.h>
#include <stdint.h>

int first_set(uint64_t n) {
	for (int i = 0; i < 64; i++) {
		if (n & ((uint64_t)1 << i)) {
			return i;
		}
	}
	return -1;
}

#ifdef PART1
#define MASKNUM 2
#define READNUM 1
#else
#define MASKNUM 3
#define READNUM 3
#define PART1 0
#endif

int main(void)
{
	FILE *fp = fopen("data/input3", "r");

	if (fp == NULL) {
		return 1;
	}

	int tp = 0;
	char buf[READNUM][60];
	while (1) {
		for (int i = 0; i < READNUM; i++) {
			if (fgets(buf[i], 60, fp) == NULL) {
				goto out;
			}
		}
		uint64_t masks[MASKNUM] = {0};
		for (int i = 0; i < MASKNUM; i++) {
			int scan = PART1 ? (int)strlen(buf[0]) / 2 : (int)strlen(buf[i]) - 1;
			for (int j = 0; j < scan; j++) {
				char c = PART1 ? buf[0][i*scan + j] : buf[i][j];
				int p = (c >= 'a') ? c - 'a' : c - 'A' + 26;
				masks[i] |= (uint64_t)1 << p;
			}
		}
		uint64_t mask = ~0;
		for (int i = 0; i < MASKNUM; i++) {
			mask &= masks[i];
		}
		tp += first_set(mask) + 1;
	}
out:
	fclose(fp);

	printf("%d\n", tp);
}
