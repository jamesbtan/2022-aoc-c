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
		int s1 = c1 - 'A';
		// 0 = lose, 1 = tie, 2 = win
		int v = c2 - 'X';
		// int v = ((s2 - s1) % 3 + 4) % 3;
		int s2 = ((v + 2) % 3 + s1) % 3;
		int s = v * 3 + s2 + 1;
		ts += s;
	}
	fclose(fp);

	printf("%d\n", ts);
}
