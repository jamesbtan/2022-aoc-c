#include <stdio.h>

int main(void)
{
	FILE *fp = fopen("data/input2", "r");
	if (fp == NULL) {
		return 1;
	}

	int ts = 0;
	char c1;
	char c2;
	while (fscanf(fp, "%c %c\n", &c1, &c2) != EOF) {
		// 0 = rock, 1 = paper, 2 = scissors
		// 0 = lose, 1 = tie, 2 = win
		int s1 = c1 - 'A';
#ifdef PART1
		int s2 = c2 - 'X';
		int v = (s2 - s1 + 4) % 3;
#else
		int v = c2 - 'X';
		int s2 = (v + 2 + s1) % 3;
#endif
		int s = v * 3 + s2 + 1;
		ts += s;
	}
	fclose(fp);

	printf("%d\n", ts);
}
