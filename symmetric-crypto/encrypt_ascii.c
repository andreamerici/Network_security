#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

#define Msize 96
#define SPACE ' '

	int taken[Msize];
	int key[Msize];

	int i, j, u, c;

	// printf("Key generation\n");
	for(i = 0; i < Msize; i++) taken[i] = 0;
	j = 0;

	while(j < Msize) {
		do {
			c = lrand48() % Msize;
		} while(taken[c] == 1);
		taken[c] = 1; key[j] = c;
		j++;
	}

	int retc;
	while((retc = fgetc(stdin)) != EOF) {

		// if something we cannot print... simply say WHAT it is
		// and exit: filter out 0x0a and transform 0x0c into SPACE
		// to preserve the number of characters!
		if (retc == 0x0a) {
			printf("\n");
			continue;
		}

                if (retc == 0x0c) {
			printf(" ");
			continue;
		}

		if(retc < SPACE || retc > 127) {
			printf("Invalid character %d-%c\n", retc, retc);
			return -1;
		}

		printf("%c", key[retc - SPACE] + SPACE);
	}
}
