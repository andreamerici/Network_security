
CC=gcc

%.o: %.c
	$(CC) -c -o $@ $<

all: attack_ascii encrypt_ascii freqfinder

attack_ascii: attack_ascii.o
	$(CC) -o $@ $^

encrypt_ascii: encrypt_ascii.o 
	$(CC) -o $@ $^

freqfinder: freqfinder.o
	$(CC) -o $@ $^

clean:
	rm -f *.o attack_ascii encrypt_ascii freqfinder
