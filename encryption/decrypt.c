#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct element {
     int src;
     char dst;
};

struct element table[256];
int elements = 0;

int main (int argc, char *argv[])
{
	// clear table
	memset (table, 0, sizeof (table));

	// read parameters
	int parnum = 1;
	while (parnum < argc) {
		if (strncmp(argv[parnum], "-0x", 3)) {
			fprintf (stderr, "Invalid parameter list\n");
			return 1;
		} 

		long code = strtol (&argv[parnum][1], NULL, 0);
		if (code < 0 || code > 255) {
			fprintf (stderr, "Invalid code, must be a number in range [0..255]\n");
			return 1;
		}
		
		parnum ++;
		if (parnum >= argc) {
			fprintf (stderr, "Missing value (last)\n");
			return 1;
		}

		char newcode = 0;
		if (argv[parnum][0] == '\\') {
			if (strlen (argv[parnum]) < 2) {
				fprintf (stderr, "Invalid special code\n");
				return 1;
			}
			if (argv[parnum][1] == 'n')
				newcode = '\n';
			else {
				fprintf (stderr, "Invalid special code\n");
				return 1;
			}
		}
		else {
			if (strlen (argv[parnum]) > 1) {
				fprintf (stderr, "Replacement is too long\n");
				return 1;
			}
			newcode = argv[parnum][0];
		}
	
		table[code].dst = newcode;
#ifdef DEBUG
		fprintf (stdout, "Replacing %02X with %c\n", (unsigned int) code, newcode);
#endif // DEBUG

		parnum ++;
	}

	// replacing bytes in binary data
	int retc;
	while ((retc = fgetc(stdin)) != EOF) {
		unsigned char readval = (unsigned char) retc;

		if (table[readval].dst != 0)
			fprintf (stdout, "%c", table[readval].dst);
		else
			fprintf (stdout, ".");
	}

	return 0;
}
