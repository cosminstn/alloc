#include <stdlib.h>
#include <stdio.h>
#include "secsalloc.h"
#include <pthread.h>
#include <errno.h>
void *allocate_memory() {
	int s = 0,i;
	int* v;
	int n = 5;
	v = (int*)secs_alloc(n * sizeof(int));
	for( i = 0; i < n; i++)
		v[i] = i;
	for(i = 0; i <n; i++)
		s = s + v[i];
	printf("Suma elementelor vectorului este: %d \n", s);
	secs_free(v);
}

//O mica observatie
//Acest test nu functioneaza
int main(int argc, char* argv[]) {
	int* vector = (int *)secs_alloc(3 * sizeof(int));
	int* v1, v2;
	pthread_t p1, p2;
	int err1 = pthread_create(&p1, NULL, allocate_memory, NULL);
	if(err1)
	{
		printf("Thread creation failed!");
		return err1;
	}
	else
		printf("Thread 1 created\n");
	int err2 = pthread_create(&p2, NULL, allocate_memory, NULL);
	if(err2)
	{
		printf("Thread creation failed!");
		return err2;
	}
	else
		printf("Thread 2 created\n");
	
	if(pthread_join(p1, NULL)) {
		perror(NULL);
		return errno;
	}

	if(pthread_join(p2, NULL)) {
		perror(NULL);
		return errno;
	}	
	return 0;
}