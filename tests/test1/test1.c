#include <stdlib.h>
#include <stdio.h>
#include "secsalloc.h"

int main(int argc, char* argv[]) {
	int* vector = (int *)secs_alloc(3 * sizeof(int));
	for(int i = 0; i < 3; i++)
	    vector[i] = i;

    for(int i = 0; i < 3; i++)
	    printf("%d\n", vector[i]);
	return 0;
}