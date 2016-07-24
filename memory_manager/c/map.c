#include "test.h"

#include <stddef.h>
#include <strings.h>
#include <stdio.h>

#define container_of(ptr, type, member) ({			\
			const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
			(type *)( (char *)__mptr - offsetof(type,member) );})

#define max_size 1024

typedef struct node
{
	int index;
	int data;
} node_t;

typedef struct block
{
	node_t node[max_size];	
	int idles[max_size];
	int idle_count;
	struct block *next;
} block_t;

block_t *head;

void mm_init()
{
}

void mm_fini()
{
	block_t *block;

	while (head) {
		block = head;
		head = head->next;
		free(block);
	}
}

void mm_expand(size_t size)
{
	block_t *block;
	int i;

	block = malloc(sizeof(block_t));
	for (i = 0; i < max_size; ++i) {
		block->node[i].index = i;
		block->idles[i] = i;
	}
	block->idle_count = max_size;
	block->next = head;
	head = block;
}

int mm_get_idle_index(block_t *block)
{
	if (block->idle_count > 0) {
		--block->idle_count;
		return block->idles[block->idle_count];
	} else {
		return -1;
	}
}

void* mm_malloc(size_t size)
{
	block_t *block;
	int index;

	block = head;

	while (block) {
		index = mm_get_idle_index(block);
		if (index != -1) {
			return &block->node[index].data;
		} else {
			block = block->next;
		}
	}

	mm_expand(size);
	index = mm_get_idle_index(head);
	return &head->node[index].data;
}

void mm_free(void *p)
{
	node_t *n;
	block_t *block;

	n = container_of(p, node_t, data);

	block = container_of((void*)(n - n->index), block_t, node);
	block->idles[block->idle_count] = n->index;
	++block->idle_count;
}

int main()
{
	mm_init();
	test(mm_malloc, mm_free);
	//test_random(mm_malloc, mm_free);
	mm_fini();
	return 0;
}

