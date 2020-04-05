#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

#define Msize 96
#define SPACE ' '

 	int dekey[Msize];

	int i, j, u, c;

	for(i = 0; i < Msize; i++) dekey[i] = -1;

	// attack code
	// create table from command line
	for (i = 1; i < argc; i += 2) {
		if (i + 1 < argc) {
			char enc = *argv[i];
			char dec = *argv[i + 1];
			dekey[enc - SPACE] = dec - SPACE;
		}
	}

	int retc;
	while((retc = fgetc(stdin)) != EOF) {
		if(retc < 0 || retc > 127) {
			printf("Invalid character %d-%c\n", retc, retc);
			return -1;
		}

		if(retc < SPACE) printf("%c", retc);
		else if(dekey[retc - SPACE] >= 0) printf("%c", dekey[retc - SPACE] + SPACE);
		else printf(".");
	}
}
