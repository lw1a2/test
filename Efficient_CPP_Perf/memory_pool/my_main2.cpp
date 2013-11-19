#include <iostream>
#include <sys/time.h>
#include <pthread.h>

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
			//һ������EXPANSION_SIZE���ڵ�
			for (int i = 0; i < EXPANSION_SIZE; ++i)
			{
				tmp = T::node_list;
				T::node_list = new node;
				T::node_list->value = (T*)(new char[sizeof(T)]);
				T::node_list->next = tmp;
			}
		}

		T* curr = T::node_list->value;

		//��node_list�ĵ�һ���ڵ��Ƴ�
		tmp = T::node_list;
		T::node_list = T::node_list->next;

		//��node_list�ĵ�һ���ڵ����used_node_list����
		node* tmp2 = T::used_node_list;
		T::used_node_list = tmp;
		T::used_node_list->next = tmp2;

		return curr;
	}

	static void free(T* doomed)
	{
		//��used_node_list�ĵ�һ���ڵ��Ƴ�
		node* tmp = T::used_node_list;
		T::used_node_list->value = doomed;
		T::used_node_list = T::used_node_list->next;

		//��used_node_list�ĵ�һ���ڵ����node_list����
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
		pthread_mutex_lock(&mutex);
		void *p = node<Rational>::alloc();
		pthread_mutex_unlock(&mutex);
		return p;
	}

	inline void operator delete(void* doomed, size_t)
	{
		pthread_mutex_lock(&mutex);
		node<Rational>::free((Rational*)doomed);
		pthread_mutex_unlock(&mutex);
	}

	//���������룬δʹ�õĽڵ�
	static node<Rational>* node_list;

	//������ʹ�õĽڵ�
	static node<Rational>* used_node_list;

	static pthread_mutex_t mutex;

private:
	int n;	 // Numerator
	int d;	 // Denominator
};

node<Rational>* Rational::node_list = NULL;
node<Rational>* Rational::used_node_list = NULL;
pthread_mutex_t Rational::mutex = PTHREAD_MUTEX_INITIALIZER;

Rational *array[1000];

void* f(void*)
{
	for (int i = 0; i < 1000; i++)
	{
		array[i] = new Rational(i);
	}
	for (int i = 0; i < 1000; i++)
	{
		delete array[i];
	}

	return 0;
}

int main()
{
	// Start timing here
	struct timeval tv, tv2;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	tv2 = tv;
	gettimeofday(&tv, NULL);

	const int threads = 500;
	pthread_t thr[threads];
	for (int j = 0; j < threads; j++)
	{
		pthread_create(thr + j, NULL, f, NULL);
	}

	for (int j = 0; j < threads; j++)
	{
		pthread_join(thr[j], NULL);
	}

	// Stop timing here
	gettimeofday(&tv2, NULL);

	cout << (tv2.tv_sec - tv.tv_sec) * 1000000 + tv2.tv_usec - tv.tv_usec << endl;

	return 0;
}


