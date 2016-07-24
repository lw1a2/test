#include "test.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>

void test(MALLOC m, FREE f)
{
	int i, j;
	int *p[1024];

	for (i = 0; i < 50000; ++i) {
		for (j = 0; j < 1024; ++j) {
			p[j] = m(sizeof(int));
			*p[j] = i + j;
		}

		for (j = 0; j < 1024; ++j) {
			f(p[j]);
		}
	}
}

void test_random(MALLOC m, FREE f)
{
	int i, j;
	int *p[1024 * 50];
	int size;

	size = sizeof(p) / sizeof(p[0]);

	bzero(p, sizeof(p));
	srandom(time(NULL));

	for (i = 0; i < size; ++i) {
		j = random() % size;
		if (p[j]) {
			f(p[j]);
			p[j] = NULL;
		} else {
			p[j] = m(sizeof(int));
		}
	}	
}
