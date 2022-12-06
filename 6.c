#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
			int found = 1;
			uint32_t mask = 0;
			for (size_t j = 0; j < d.len; j++) {
				uint32_t bit = 1 << (*deq_char_get(&d, j) - 'a');
				if (mask & bit) {
					found = 0;
					break;
				} else {
					mask |= bit;
				}
			}
			deq_char_popf(&d);
			if (found) break;
		}
	}
	printf("%d\n", i+1);
	fclose(fp);
}
