#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	if (argc < 2) {
		fprintf (stderr, "Missing keyvalue\n");
		return 1;
	}

	long key = strtol (argv[1], NULL, 0);
	if (key > 255) {
		fprintf (stderr, "Key must be a number in range [0..255]\n");
		return 1;
	}
	
	unsigned char key8 = (unsigned char) key;
	
	int retc;
	while ((retc = fgetc(stdin)) != EOF) {
		unsigned char readval = (unsigned char) retc;
		readval ^= key8;

		fwrite (&readval, 1, 1, stdout);
	}

	return 0;
}
