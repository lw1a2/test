#include <iostream>
#include <sys/time.h>

using namespace std;

class NextOnFreeList
{
public:
	NextOnFreeList *next;
};

class Rational
{
public:
	Rational (int a = 0, int b = 1 ) : n(a), d(b) {}

	inline void *operator new(size_t size);
	inline void operator delete(void *doomed, size_t size);

	static void newMemPool() { expandTheFreeList();}
	static void deleteMemPool();

private:
	static NextOnFreeList *freeList;	// A free list of
										// Rational objects.
	static void expandTheFreeList();
	enum
	{
		EXPANSION_SIZE = 32
	};

	int n;	 // Numerator
	int d;	 // Denominator
};

inline
void * Rational::operator new(size_t size)
{
	if (0 == freeList)// If the list is empty, fill it up.
	{
		expandTheFreeList();
	}

	NextOnFreeList *head = freeList;
	freeList = head->next;

	return head;
}

inline
void Rational::operator delete(void *doomed, size_t size)
{
	NextOnFreeList *head = static_cast <NextOnFreeList *>(doomed);

	head->next = freeList;
	freeList  = head;
}

void Rational::expandTheFreeList()
{
	// We must allocate an object large enough to contain the next
	// pointer.
	size_t size = (sizeof(Rational) > sizeof(NextOnFreeList *)) ?
				  sizeof(Rational) : sizeof(NextOnFreeList *);

	NextOnFreeList *runner =
	static_cast <NextOnFreeList *>((void*)new char [size]);

	freeList =  runner;
	for (int i = 0; i < EXPANSION_SIZE; i++)
	{
		runner->next =
		static_cast <NextOnFreeList *>((void*)new char [size]);
		runner = runner->next;
	}

	runner->next = 0;
}

void Rational::deleteMemPool()
{
	NextOnFreeList *nextPtr;
	for (nextPtr = freeList; nextPtr != NULL; nextPtr = freeList)
	{
		freeList = freeList->next;
		delete [] nextPtr;
	}
}

NextOnFreeList *Rational::freeList = 0;



int main()
{
	Rational *array[1000];

	Rational::newMemPool();

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

	Rational::deleteMemPool();

	return 0;
}


