#ifndef EXTRAFUNC_H
#define EXTRAFUNC_H
/* ^^ these are the include guards */

// Function copy a sub section of the original array from the designated startPoint
double *copyFrom(double *orgAr, int arLen, int startPoint);

// Function copy original array from 0 to secify arLen
double  *copyArray(double *orgAr, int arLen);

// Generate a random array with length arrLen
void arrayGen(double *arr, int arrLen);

// Compare values in arr to model. Return 1 if mismatch
int arrayCheck(double *model, double *arr, int arrLen);

// Print contents of array for a sepcify length
void printArray(double *ar, int arrLen);

// Function to determine if string is numeric. Return 1 on success
int isInteger(char *str);

#endif