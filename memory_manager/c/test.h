#ifndef __TEST_H__
#define __TEST_H__

#include <stdlib.h>

typedef void* (*MALLOC)(size_t size);
typedef void (*FREE)(void* p);

void test(MALLOC m, FREE f);
void test_random(MALLOC m, FREE f);

#endif
