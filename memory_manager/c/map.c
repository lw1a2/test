#include "test.h"

#include <stddef.h>
#include <strings.h>
#include <stdio.h>

#define container_of(ptr, type, member) ({			\
			const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
			(type *)( (char *)__mptr - offsetof(type,member) );})

#define max_size 32

typedef struct node
{
	char is_used;	// 0: idle, 1: used
	int index;
	int data;
} node_t;

typedef struct _block
{
	node_t node[max_size];	
	struct _block *next;
	char all_used;
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
		block->node[i].is_used = 0;
		block->node[i].index = i;
	}
	block->all_used = 0;
	block->next = head;
	head = block;
}

int mm_get_idle_index(block_t *block)
{
	int i;

	for (i = 0; i < max_size; ++i) {
		if (block->node[i].is_used == 0) {
			return i;
		}
	}

	return -1;
}

void* mm_malloc(size_t size)
{
	block_t *block;
	int index;

	block = head;

	while (block) {
		if (!block->all_used) {
			index = mm_get_idle_index(block);
			if (index != -1) {
				block->node[index].is_used = 1;
				return &block->node[index].data;
			} else {
				block->all_used = 1;
			}
		}
		block = block->next;
	}

	mm_expand(size);
	
	head->node[0].is_used = 1;
	return &head->node[0].data;
}

void mm_free(void *p)
{
	node_t *n;
	block_t *block;

	n = container_of(p, node_t, data);
	n->is_used = 0;

	block = container_of((void*)(n - n->index), block_t, node);
	block->all_used = 0;
}

int main()
{
	mm_init();
	test(mm_malloc, mm_free);
	mm_fini();
	return 0;
}

