#include "test.h"

void test(MALLOC m, FREE f)
{
	int i, j;
	int *p[1024];

	for (i = 0; i < 50000; ++i) {
		for (j = 0; j < 1024; ++j) {
			p[j] = m(sizeof(int));
			*p[j] = i;
		}

		for (j = 0; j < 1024; ++j) {
			f(p[j]);
		}
	}
}
