// Get string from user and determine if it's a palindrome

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int main(void)
{
	// Prompt for string
	promptf("Enter string: ");

	// Get string
	char *str = readline(stdin, 1 << 5);
	if (!str) return READ_LINE_ERROR;

	// Check if string is palindrome
	int result = ispalindrome(str);
	if (result == -1) { free(str); return PALINDROME_ERROR; }

	// Print result
	printf("\"%s\" is a%s palindrome.\n", str, (result) ? "" : " not");
	free(str);

	return 0;
}
