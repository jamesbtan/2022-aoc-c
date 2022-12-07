#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ds/vec.h"

enum Command {
	CD_IN,
	CD_OUT,
	LS,
};

enum Kind {
	CMD,
	DIR,
	I_FILE,
};

DEF_VECT(int, i);

struct Dir {
	struct Dir *parent;
	vec_i *files;
	// pointer to vec of dirs
	void *dirs;
	int size;
};

//cd .. = curr = curr->parent;
//cd x = vec_dir_push((vec_dir *)curr->dirs, 
DEF_VECT(struct Dir *, dir);

struct Dir *create_dir(struct Dir *parent) {
	struct Dir *d = malloc(sizeof(struct Dir));
	d->parent = parent;
	d->files = calloc(1, sizeof(vec_i));
	d->dirs = calloc(1, sizeof(vec_dir));
	d->size = 0;
	return d;
}

int main(void)
{
	FILE *fp = fopen("data/input7.ex", "r");
	struct Dir *root = NULL;
	struct Dir *curr = root;
	/*
	root->parent = NULL;
	root->files = calloc(1, sizeof(vec_i));
	root->dirs = calloc(1, sizeof(vec_dir));
	*/
	char buf[64];
	while (fgets(buf, 64, fp) != NULL) {
		char *token = strtok(buf, " ");
		enum Kind k;
		enum Command c;
		for (int i = 0; token; i++) {
			switch (i) {
			case 0:
				switch (token[0]) {
				case '$':
					k = CMD;
					break;
				case 'd':
					struct Dir *d = create_dir(curr);
					break;
				default:
					vec_i_push(curr->files, strtol(token, NULL, 10));
				}
				break;
			case 1:
				break;
			}
			token = strtok(NULL, " ");
		}
	}
	fclose(fp);
}
