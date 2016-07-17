#include "test.h"

#include <stddef.h>
#include <strings.h>
#include <assert.h>

#define container_of(ptr, type, member) ({			\
			const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
			(type *)( (char *)__mptr - offsetof(type,member) );})

#define max_size 32

typedef struct _node
{
	char map[max_size];	// 0: idle, 1: used
	int data[max_size];
	struct _node *next;
	char all_used;
} node;

node *head;

void mm_init()
{
}

void mm_fini()
{
	node *n;

	while (head) {
		n = head;
		head = head->next;
		free(n);
	}
}

void mm_expand(size_t size)
{
	node *n;

	n = malloc(sizeof(node));
	bzero(n->map, sizeof(n->map));
	n->all_used = 0;
	n->next = head;
	head = n;
}

int mm_get_idle_index(node *n)
{
	int i;

	for (i = 0; i < sizeof(n->map); ++i) {
		if (n->map[i] == 0) {
			return i;
		}
	}

	return -1;
}

void* mm_malloc(size_t size)
{
	node *n;
	int index;

	n = head;

	while (n) {
		if (!n->all_used) {
			index = mm_get_idle_index(n);
			if (index != -1) {
				n->map[index] = 1;
				return &n->data[index];
			} else {
				n->all_used = 1;
			}
		}
		n = n->next;
	}

	mm_expand(size);
	
	head->map[0] = 1;
	return &head->data[0];
}

void mm_free(void *p)
{
	node *n;
	int index;
	int *pi;

	n = head;
	pi = p;
	
	while (n) {
		if (n->data <= pi && pi < n->data + max_size) {
			index = pi - n->data;
			n->map[index] = 0;
			n->all_used = 0;
			return;
		}

		n = n->next;
	}

	assert(0);
}

int main()
{
	mm_init();
	test(mm_malloc, mm_free);
	mm_fini();
	return 0;
}

