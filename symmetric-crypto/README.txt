Before going on build the executables with:

	$: make

Encrypt the clear-text file "rfc2360.txt" and take a look at the cipher-text:

	$: cat rfc2360.txt | ./encrypt_ascii > rfc2360enc.txt
	$: less rfc2360enc.txt

It is evident that not all ASCII code have been modified, e.g., the RETURN code
was not touched, and FF (0x0c) was transformed into a SPACE.

Compute the occurrence frequency tables and display on screen:

	$: cat rfc2360.txt | ./freqfinder | less
	$: cat rfc2360enc.txt | ./freqfinder | less

The top occurring codes in the clear-text are (first six after SPACE):

	$: cat rfc2360.txt | ./freqfinder | less

	32      11376   ' '
	101     3858    'e'
	116     3053    't'
	111     2477    'o'
	110     2303    'n'
	105     2253    'i'
	97      2183    'a'

Although the codes in the cipher-text have been substituted, the frequency
values are exactly the same.

Try to mount a frequency analysis attack to decrypt file "rfcxxxxenc.txt".
First, compute the frequency table:

	$: cat rfcxxxxenc.txt | ./freqfinder | less

	114     6716    'r'
	87      2475    'W'
	53      1842    '5'
	54      1580    '6'
	72      1524    'H'
	101     1495    'e'
	39      1494    '''

We can imagine that code _114_ is SPACE, code _87_ is letter 'e', code _53_ is
letter 't' and so on and so forth according to the previous frequency table.

Execute attack_ascii building the command line as follows

	$: cat rfcxxxxenc.txt | \
		./attack_ascii  r " " W e 5 t 6 o H n e i "'" a | less

Now look at line

	.tat.. o. t.i. .e.o

It could be something like

	Status of this memo

So we can add other letters by checking on the encrypted version how they were
encrypted. Line is:

	.tat.. o. t.i. .e.o
	Status of this Memo
	D5'5dkr6-r59ekr&WP6

Pay attention to the two M and m!! they cannot be differently encrypted!! So
one must be capital.

We can run:

	$: cat rfcxxxxenc.txt | \
		./attack_ascii  r " " W e 5 t 6 o H n e i "'" a D S d u k s "-" f 9 h k s "&" M P m | \
		less

HOMEWORK:
	1) try guessing which RFC is.
	2) try to decrypt file xxxxxxenc.txt !!
