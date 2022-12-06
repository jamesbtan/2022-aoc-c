#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ds/deq.h"
DEF_DEQT(char);

#ifdef PART1
#define NUM 4
#else
#define NUM 14
#endif

int main(void)
{
	FILE *fp = fopen("data/input6", "r");
	char c;
	deq_char d = deq_char_init_cap(NUM);
	int i;
	for (i = 0; (c = fgetc(fp)) != EOF; i++) {
		if (i < NUM-1) {
			deq_char_pushb(&d, c);
		} else {
			assert(d.len == NUM-1);
			deq_char_pushb(&d, c);
			int diff = 1;
			for (size_t j = 0; j < d.len; j++) {
				for (size_t k = 0; k < j; k++) {
					if (*deq_char_get(&d, j) == *deq_char_get(&d, k)) {
						diff = 0;
						goto out;
					}
				}
			}
out:
			deq_char_popf(&d);
			if (diff) break;
		}
	}
	printf("%d\n", i+1);
	fclose(fp);
}
