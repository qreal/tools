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
	snprintf(result, maxLen, "%d.%d", (int)f, ((int)((f - (int)f) * 1000)));
	return result;
}

char *other_to_string(void *arr) {
	int const maxLen = 14;
	char *result = (char *)malloc(maxLen);
	snprintf(result, maxLen, "0x%0", (int)arr);
	return result;
}
