#ifndef UTIL_H
#define UTIL_H

// Includes

#include <stdio.h>

// Defines

// Error code for readline
#define READ_LINE_ERROR  1
// Error code for ispalindrome
#define PALINDROME_ERROR 2

// Prototypes

// Print message and flush stdout buffer
int promptf(const char format[], ...);
// Dynamically read line from a file
char *readline(FILE *fp, size_t size);
// Determine if string is a palindrome
int ispalindrome(const char str[]);

#endif // UTIL_H
