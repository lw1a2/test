#include "test.h"

#include <stddef.h>

#define container_of(ptr, type, member) ({			\
			const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
			(type *)( (char *)__mptr - offsetof(type,member) );})

typedef struct _node
{
	union {
		int data;
		struct _node *next;
	};
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
	const int max_size = 1024;
	int i;
	node *n;

	for (i = 0; i < max_size; ++i) {
		n = malloc(sizeof(node));
		n->next = head;
		head = n;
	}
}

void* mm_malloc(size_t size)
{
	void *p;

	if (!head) {
		mm_expand(size);
	}

	p = &head->data;
	head = head->next;

	return p;
}

void mm_free(void *ptr)
{
	node *n;
	
	n = container_of(ptr, node, data);

	n->next = head;
	head = n;
}

int main()
{
	mm_init();
	test(mm_malloc, mm_free);
	//test_random(mm_malloc, mm_free);
	mm_fini();
	return 0;
}

