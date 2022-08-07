#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

// Static prototypes

// Safe self-realloc
static void *xrealloc(void **ptr, size_t size);
// Convert string to alpha
static char *toalphas(const char str[]);
// Convert string to lower
static char *tolowers(const char str[]);
// Reverse string
static char *reverses(const char str[]);

// Print a message and flush stdout buffer
int promptf(const char format[], ...)
{
	va_list args;
	va_start(args, format);
	int ret = vprintf(format, args);
	va_end(args);

	fflush(stdout);

	return ret;
}

// Safe self-realloc
static void *xrealloc(void **ptr, size_t size)
{
	void *res = realloc(*ptr, size);
	if (!res) {
		perror("xrealloc: REALLOC ERROR");
		fputs("Failed to reallocate memory\n", stderr);
		free(*ptr);
	}
	return res;
}

// Dynamically read a line from a file
char *readline(FILE *fp, size_t size)
{
	// Start with a chunk of memory
	size_t len = 0, chunk = size;
	char *str = malloc(chunk);
	if (!str) {
		perror("readline: MALLOC ERROR");
		fputs("Failed to allocate memory\n", stderr);
		return NULL;
	}

	// Read until EOF or EOL is reached
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n' && ch != '\r') {
		str[len++] = ch;
		// Allocate more memory as needed
		if (len == chunk) {
			str = xrealloc((void **)&str, chunk *= 2);
			if (!str) return NULL;
		}
	}
	str[len++] = '\0';

	return xrealloc((void **)&str, len);
}

// Convert string to alpha
static char *toalphas(const char str[])
{
	size_t len = strlen(str);

	// Get number of alpha characters in string
	size_t alphalen = 0;
	for (int i = 0; i < len; ++i) if (isalpha(str[i])) ++alphalen;

	// Allocate memory for alpha string
	char *alpha = malloc(alphalen + 1);
	if (!alpha) {
		perror("toalphas: MALLOC ERROR");
		fprintf(stderr, "Failed to allocate memory for alpha: %s\n", str);
		return NULL;
	}

	// Construct alpha string
	for (int i = 0, j = 0; i < len; ++i) if (isalpha(str[i]))
		alpha[j++] = str[i];
	alpha[alphalen] = '\0';

	return alpha;
}

// Convert string to lower
static char *tolowers(const char str[])
{
	size_t len = strlen(str);

	// Allocate memory for lower string
	char *lower = malloc(len + 1);
	if (!lower) {
		perror("tolowers: MALLOC ERROR");
		fprintf(stderr, "Failed to allocate memory for lower: %s\n", str);
		return NULL;
	}

	// Construct lower string
	for (int i = 0; i < len; ++i) lower[i] = tolower(str[i]);
	lower[len] = '\0';

	return lower;
}

// Reverse string
static char *reverses(const char str[])
{
	size_t len = strlen(str);

	// Allocate memory for reverse string
	char *rev = malloc(len + 1);
	if (!rev) {
		perror("reverses: MALLOC ERROR");
		fprintf(stderr, "Failed to allocate memory for reverse: %s\n", str);
		return NULL;
	}

	// Construct reverse string
	for (int i = 0; i < len; ++i) rev[i] = str[len - i - 1];
	rev[len] = '\0';

	return rev;
}

// Determine if string is a palindrome
int ispalindrome(const char str[])
{
	// Convert and store alpha lower string
	
	// Make alpha string
	char *base = toalphas(str);
	if (!base) return -1;

	// Make lower string
	char *tmp = tolowers(base);
	if (!tmp) { free(base); return -1; }

	// Swap tmp back to base
	free(base);
	base = tmp;

	// Construct reverse string from alpha lower string
	char *rev = reverses(base);
	if (!rev) { free(base); return -1; }

	// Compare alpha lower string to its reverse
	int ret = !strcmp(base, rev);

	free(base);
	free(rev);

	return ret;
}
