#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int comp(const void *a, const void *b) {
	char av = *(char *) a;
	char bv = *(char *) b;
	return (av > bv) - (bv > av);
}

int main(void)
{
	FILE *fp = fopen("data/input3", "r");

	if (fp == NULL) {
		return 1;
	}

	int tp = 0;
#ifdef PART1
	char buf[60];
	while (fgets(buf, 60, fp) != NULL) {
		int hlen = strlen(buf) / 2;
		qsort(buf, hlen, sizeof(char), comp);
		qsort(buf+hlen, hlen, sizeof(char), comp);
		int i, j;
		for (i = 0, j = hlen; buf[i] != buf[j];) {
			if (buf[i] < buf[j]) {
				i++;
			} else {
				j++;
			}
		}
		char c = buf[i];
#else
	char buf[3][60];
	while (fscanf(fp, "%s\n%s\n%s\n", buf[0], buf[1], buf[2]) != EOF) {
		for (int i = 0; i < 3; i++) {
			qsort(buf[i], strlen(buf[i]), sizeof(char), comp);
		}
		int ind[3] = {0};
		while (1) {
			int same = 1;
			int min = buf[0][ind[0]];
			int mini = 0;
			for (int i = 1; i < 3; i++) {
				if (buf[0][ind[0]] != buf[i][ind[i]]) {
					same = 0;
				}
				if (buf[i][ind[i]] < min) {
					min = buf[i][ind[i]];
					mini = i;
				}
			}
			if (same) break;
			ind[mini]++;
		}
		char c = buf[0][ind[0]];
#endif
		int p = (c >= 'a') ? c - 'a' + 1 : c - 'A' + 27;
		tp += p;
	}
	fclose(fp);

	printf("%d\n", tp);
}
