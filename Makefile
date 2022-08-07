.POSIX:

all: palindrome

palindrome: palindrome.o util.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ palindrome.o util.o
palindrome.o: palindrome.c util.h
util.o: util.c util.h

clean:
	@rm -f palindrome palindrome.o util.o
