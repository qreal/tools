#include "trik_studio_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat(char *str1, char *str2) {
	char *result = (char *)malloc(strlen(str1) + strlen(str2));
	strcpy(result, str1);
	return strcat(result, str2);
}

char *int_to_string(int i) {
	int const maxLen = 11;
	char *result = (char *)malloc(maxLen);
	snprintf(result, maxLen, "%d", i);
	return result;
}


char *float_to_string(float f) {
	int const maxLen = 15;
	char *result = (char *)malloc(maxLen);
	snprintf(result, maxLen, "%.3f", f);
	return result;
}

char *array_to_string(void *arr) {
	return "<Array convertion to string is not supported for C language>";
}
