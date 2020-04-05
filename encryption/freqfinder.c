#include <stdio.h>
#include <ctype.h>

struct codefreq {
     int code;
     int freq;
};

struct codefreq freqtable[256];

int main (int argc, char* argv[])
{
	int jj;

	// clean table
	for (jj = 0; jj < 256; jj ++) {
		freqtable[jj].code = jj;
		freqtable[jj].freq = 0;
	}

	// read input
	int retc;
	while((retc = fgetc(stdin)) != EOF) {
		unsigned char code = (unsigned char) retc;
		freqtable[code].freq ++;
	}

	// sort table
	int indx, indx2;
	int flipped;

	indx = 1;
	do {
		flipped = 0;
		for (indx2 = 255; indx2 >= indx; --indx2) {
			if(freqtable[indx2].freq >
			   freqtable[indx2 - 1].freq) {
				int tmpfreq = freqtable[indx2].freq;
				int tmpcode = freqtable[indx2].code;
				freqtable[indx2].freq =
					freqtable[indx2 -1].freq;
				freqtable[indx2].code =
					freqtable[indx2 -1].code;
				freqtable[indx2 -1].freq = tmpfreq;
				freqtable[indx2 -1].code = tmpcode;
				flipped = 1;
			}
		}
	} while ((++indx < 256) && flipped);

	// print table
	printf ("CODE FREQ\n");
	for (jj = 0; jj < 256; jj ++) {
		if (freqtable[jj].freq == 0) continue;

		int code = freqtable[jj].code;
		if (code == ' ') {
			fprintf (stdout, "0x%02X %d (' ')\n", code, freqtable[jj].freq);
		} else if (code == 0xa || code == 0xd) {
			fprintf (stdout, "0x%02X %d ('\\n')\n", code, freqtable[jj].freq);
		} else if (isascii (code)) {
			fprintf (stdout, "0x%02X %d (%c)\n", code, freqtable[jj].freq, (char) code);
		} else {
			fprintf (stdout, "0x%02X %d\n", code, freqtable[jj].freq);
		}
	}
}
