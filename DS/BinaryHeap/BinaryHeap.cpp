#include <vector>

using namespace std;

class UnderflowException
{
};

template <typename Comparable>
class BinaryHeap
{
  public:
    explicit BinaryHeap( int capacity = 100 ) : currentSize(0), array(100)
    {
    }

    explicit BinaryHeap( const vector<Comparable> & items ) 
    : currentSize(items.size()), array(items.size() + 10)
    {
        for (int i = 0; i < items.size(); ++i)
        {
            array[i + 1] = items[i];
        }

        buildHeap();
    }

    bool isEmpty( ) const
    {
        return currentSize == 0;
    }

    const Comparable & findMin( ) const
    {
        if (isEmpty())
        {
            throw UnderflowException();
        }
        return array[1];
    }

    void insert( const Comparable & x )
    {
        if (++currentSize > array.size())
        {
            array.resize(array.size() * 2);
        }

        int hole = currentSize;
        for (; hole > 1 && x < array[hole / 2]; hole /= 2)
        {
            array[hole] = array[hole / 2];
        }
        array[hole] = x;
    }

    void deleteMin( )
    {
        if (isEmpty())
        {
            throw UnderflowException();
        }
        array[1] = array[currentSize--];
        percolateDown(1);
    }

    void deleteMin( Comparable & minItem )
    {
        if (isEmpty())
        {
            throw UnderflowException();
        }
        minItem = array[1];
        array[1] = array[currentSize--];
        percolateDown(1);
    }

    void makeEmpty( );

  private:
    int                currentSize;  // Number of elements in heap
    vector<Comparable> array;        // The heap array

    void buildHeap( )
    {
        for (int i = currentSize / 2; i > 0; i--)
        {
            percolateDown(i);
        }
    }

    void percolateDown( int hole )
    {
        int tmp = array[hole];

        for (int child = 0; hole * 2 <= currentSize; hole = child)
        {
            child = hole * 2;
            if (child != currentSize && array[child + 1] < array[child])
            {
                ++child;
            }
            if (tmp > array[child])
            {
                array[hole] = array[child];
            }
        }
        array[hole] = tmp;
    }
};

int main()
{
    return 0;
}

