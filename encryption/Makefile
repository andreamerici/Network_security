SRCS:=$(wildcard *.c)
EXES:=$(patsubst %.c,%,$(SRCS))

all: $(EXES)

%: %.c
	gcc -Wall -o $@ $< $(LDFLAGS)

clean:
	rm -f $(EXES)
