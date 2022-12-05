#include <stdio.h>

int main(void)
{
	FILE *fp = fopen("data/input5", "r");
	int inds[9] = {0};
	char stks[9][80] = {0};
	int hpos = 0;
	char c;
	while ((c = fgetc(fp)) != EOF) {
		if (c == '[') {
			char l = fgetc(fp);
			hpos++;
			int i = hpos / 4;
			fgetc(fp);
			hpos++;
			stks[i][inds[i]] = l;
			inds[i]++;
		} else if (c == '\n') {
			hpos = -1;
		} else if (c != ' ') {
			break;
		}
		hpos++;
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < inds[i] / 2; j++) {
			int tmp = stks[i][j];
			stks[i][j] = stks[i][inds[i]-j-1];
			stks[i][inds[i]-j-1] = tmp;
		}
	}
	for (int i = 0; i < 9; i++) {
		printf("%d:", i);
		for (int j = 0; j < inds[i]; j++) {
			if (j != 0) putchar(',');
			printf("%c", stks[i][j]);
		}
		putchar('\n');
	}
	puts("====");
	char buf[60];
	fgets(buf, 60, fp);
	fgets(buf, 60, fp);
	while (fgets(buf, 60, fp) != NULL) {
		int src, dst, amt;
		sscanf(buf, "move %d from %d to %d\n", &amt, &src, &dst);
		src--;
		dst--;
#ifdef PART1
		for (int i = 0; i < amt; i++) {
			stks[dst][inds[dst]++] = stks[src][--inds[src]];
		}
#else
		inds[src] -= amt;
		for (int i = 0; i < amt; i++) {
			stks[dst][inds[dst]++] = stks[src][inds[src]++];
		}
		inds[src] -= amt;
#endif
		printf("%d X %d > %d\n", amt, src, dst);
		for (int i = 0; i < 9; i++) {
			printf("%d:", i);
			for (int j = 0; j < inds[i]; j++) {
				if (j != 0) putchar(',');
				printf("%c", stks[i][j]);
			}
			putchar('\n');
		}
		puts("====");
	}
	for (int i = 0; i < 9; i++) {
		printf("%c", inds[i] != 0 ? stks[i][inds[i]-1] : '-');
	}
	putchar('\n');
	fclose(fp);
}
