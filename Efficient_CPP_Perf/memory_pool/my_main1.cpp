#include <iostream>
#include <sys/time.h>

using namespace std;

const int EXPANSION_SIZE = 32;

template <class T>
class node
{
public:
	T* value;
	node* next;
	static void* alloc()
	{
		node* tmp = NULL;
		if (!T::node_list)
		{
			//一次申请EXPANSION_SIZE个节点
			for (int i = 0; i < EXPANSION_SIZE; ++i)
			{
				tmp = T::node_list;
				T::node_list = new node;
				T::node_list->value = (T*)(new char[sizeof(T)]);
				T::node_list->next = tmp;
			}
		}

		T* curr = T::node_list->value;

		//将node_list的第一个节点移除
		tmp = T::node_list;
		T::node_list = T::node_list->next;

		//将node_list的第一个节点放入used_node_list队列
		node* tmp2 = T::used_node_list;
		T::used_node_list = tmp;
		T::used_node_list->next = tmp2;

		return curr;
	}

	static void free(T* doomed)
	{
		//将used_node_list的第一个节点移除
		node* tmp = T::used_node_list;
		T::used_node_list->value = doomed;
		T::used_node_list = T::used_node_list->next;

		//将used_node_list的第一个节点放入node_list队列
		node* tmp2 = T::node_list;
		T::node_list = tmp;
		T::node_list->next = tmp2;
	}
};

class Rational
{
public:
	Rational (int a = 0, int b = 1 ) : n(a), d(b) {}

	inline void *operator new(size_t)
	{
		return node<Rational>::alloc();
	}

	inline void operator delete(void* doomed, size_t)
	{
		node<Rational>::free((Rational*)doomed);
	}

	//保存已申请，未使用的节点
	static node<Rational>* node_list;

	//保存已使用的节点
	static node<Rational>* used_node_list;

private:
	int n;	 // Numerator
	int d;	 // Denominator
};

node<Rational>* Rational::node_list = NULL;
node<Rational>* Rational::used_node_list = NULL;

int main()
{
	Rational *array[1000];

	// Start timing here
	struct timeval tv, tv2;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	tv2 = tv;
	gettimeofday(&tv, NULL);

	for (int j = 0; j < 500; j++)
	{
		for (int i = 0; i < 1000; i++)
		{
			array[i] = new Rational(i);
		}
		for (int i = 0; i < 1000; i++)
		{
			delete array[i];
		}
	}

	// Stop timing here
	gettimeofday(&tv2, NULL);

	cout << (tv2.tv_sec - tv.tv_sec) * 1000000 + tv2.tv_usec - tv.tv_usec << endl;

	return 0;
}


