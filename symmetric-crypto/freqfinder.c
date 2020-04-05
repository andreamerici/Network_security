#include <stdio.h>

struct codefreq {
     int code;
     int freq;
};

int main(int argc, char* argv[])
{
#define ASCIIMAX 128
#define SPACE ' '
	struct codefreq codefreq_table[ASCIIMAX];
	int i, retc;

	for(i = 0; i < ASCIIMAX; i++) {
		codefreq_table[i].code = i;
		codefreq_table[i].freq = 0;
	}

	while((retc = fgetc(stdin)) != EOF) {
		// filter out non printable characters,
		// only accept 0x0a and 0x0c
		// and transform the latter into 0x0a
		if (retc == 0x0a || retc == 0x0c) {
			codefreq_table[0x0a].freq++;
		}
		else if(retc < SPACE || retc > 127) {
			printf("Invalid character %d %c\n", retc, retc);
			return 1;
		}
		else {
			codefreq_table[retc].freq++;
		}
	}

	// sort the table
	int indx, indx2, temp1, temp2;
	int flipped;

	indx = 1;
	do {
		flipped = 0;
		for (indx2 = ASCIIMAX - 1; indx2 >= indx; --indx2) {
			if(codefreq_table[indx2].freq >
			   codefreq_table[indx2 - 1].freq) {
				int tmpfreq = codefreq_table[indx2].freq;
				int tmpcode = codefreq_table[indx2].code;
				codefreq_table[indx2].freq =
					codefreq_table[indx2 -1].freq;
				codefreq_table[indx2].code =
					codefreq_table[indx2 -1].code;
				codefreq_table[indx2 -1].freq = tmpfreq;
				codefreq_table[indx2 -1].code = tmpcode;
				flipped = 1;
			}
		}
	} while ((++indx < ASCIIMAX) && flipped);

	// print table, but skip non printable ascii char
	// and check frequency is ZERO!
	for(i = 0; i < ASCIIMAX; i++) {
		if (codefreq_table[i].freq == 0) continue;

		if (codefreq_table[i].code == '\n') {
			printf("%d\t%d\t'\\n'\n",
			       codefreq_table[i].code,
			       codefreq_table[i].freq);
		}
		else {
			if (codefreq_table[i].code < SPACE) {
				if (codefreq_table[i].freq != 0) {
					fprintf(stderr,
						"Non printable char (code %d) found with freq > 0\n",
						codefreq_table[i].code);
					return 1;
				}
			}
			else {
				printf("%d\t%d\t'%c'\n",
				       codefreq_table[i].code,
				       codefreq_table[i].freq,
				       codefreq_table[i].code);
			}
		}
	}
}
