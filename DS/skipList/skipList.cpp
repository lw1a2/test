#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

using namespace std;

template <typename T>
struct Node
{
    T value;
    Node* prev;
    Node* next;
    Node* up;
    Node* down;
    Node() : value(numeric_limits<T>::min()), prev(NULL), next(NULL), up(NULL), down(NULL)
    {
    }
    Node(const T& v) : value(v), prev(NULL), next(NULL), up(NULL), down(NULL)
    {
    }
};

namespace std
{
template <>
string numeric_limits<string>::min()
{
    return "";
}
}

template <typename T>
class SkipList
{
public:
    SkipList()
    {
        srand(time(NULL));
        //��ͷ��������Сֵ
        topHead = bottomHead = new Node<T>;
    }

    Node<T>* search(const T& value)
    {
        //����ߵ�����ʼ����
        Node<T>* p = topHead;
        Node<T>* prev = NULL;
        while (p)
        {
            prev = p;
            while (p)
            {
                if (value == p->value)
                {
                    return p;
                }
                if (p->value < value)
                {
                    p = p->next;
                }
                else
                {
                    //����һ���ڵ�
                    p = p->prev;
                    //������
                    if (p)
                    {
                        p = p->down;
                    }
                }
            }
            //��һ�㶼û�ҵ������½�һ��
            if (prev->down)
            {
                p = prev->down;
            }
        }

        return NULL;
    }

    void insert(const T& value)
    {
        //����͵����ҵ�����λ�ã�����
        Node<T>* newNode = insertIntoList(bottomHead, value);

        //�Ƿ���Ҫ���뵽�ߵ�����
        int coin = rand();
        Node<T>* p = bottomHead;
        Node<T>* newNodeHighLevel = NULL;
        while (coin % 2)
        {
            //���뵽���ߵ�����
            if (p->up)
            {
                newNodeHighLevel = insertIntoList(p->up, value);
            }
            else
            {
                //û�и��ߵ�������ѵ�ǰ���ĵ�һ���ڵ��������γ�����
                Node<T>* head = new Node<T>;    //��ͷ��������Сֵ
                head->down = p;
                p->up = head;
                topHead = head;
                //���½ڵ���뵽������
                newNodeHighLevel = insertIntoList(head, value);
            }
            newNodeHighLevel->down = newNode;
            newNode->up = newNodeHighLevel;
            p = p->up;
            newNode = newNodeHighLevel;
            coin = rand();
        }
    }

    void eraseWithHead(const T& value)
    {
        Node<T>* p = search(value);
        Node<T>* tmp = NULL;

        while (p)
        {
            if (p->prev)
            {
                p->prev->next = p->next;
            }
            if (p->next)
            {
                p->next->prev = p->prev;
            }

            //����Ϊ�գ���ɾ�������ͷ��㣨���һ����topHead��bottomHead�ᱣ����
            if (!topHead->next && topHead != bottomHead)
            {
                tmp = topHead;
                topHead = topHead->down;
                if (topHead)
                {
                    topHead->up = NULL;
                }
                delete tmp;
            }
            tmp = p;
            p = p->down;
            delete tmp;
        }
    }

    void erase(const T& value)
    {
        Node<T>* p = search(value);
        Node<T>* tmp = NULL;

        while (p)
        {
            if (p->prev)
            {
                p->prev->next = p->next;
            }
            if (p->next)
            {
                p->next->prev = p->prev;
            }

            tmp = p;
            p = p->down;
            delete tmp;
        }
    }

    void print()
    {
        int i = 0;
        Node<T>* pLevel = topHead;
        Node<T>* p = NULL;
        while (pLevel)
        {
            cout << i++ << ": ";
            p = pLevel->next;
            while (p)
            {
                cout << p->value << " ";
                p = p->next;
            }
            cout << endl;
            pLevel = pLevel->down;
        }
    }

    ~SkipList()
    {
        Node<T>* pLevel = topHead;
        Node<T>* p = NULL;
        Node<T>* tmp = NULL;
        while (pLevel)
        {
            p = pLevel;
            pLevel = pLevel->down;
            while (p)
            {
                tmp = p;
                p = p->next;
                delete tmp;
            }
        }
    }

private:
    Node<T>* insertIntoList(Node<T>* head, const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        Node<T>* p = head->next;
        Node<T>* prev = NULL;
        while (p)
        {
            if (p->value < value)
            {
                prev = p;
                p = p->next;
            }
            else
            {
                //����һ���ڵ�
                p = p->prev;
                //���½ڵ���뵽������
                newNode->next = p->next;
                p->next = newNode;
                newNode->prev = newNode->next->prev;
                newNode->next->prev = newNode;
                return newNode;
            }
        }
        //�������Ҳ���λ��
        if (!p)
        {
            if (prev)   //����Ϊ�գ�����ӵ���β
            {
                prev->next = newNode;
                newNode->prev = prev;
            }
            else        //����һ��ʼ���ǿյ�
            {
                head->next = newNode;
                newNode->prev = head;
            }
        }
        return newNode;
    }

    Node<T>* topHead;
    Node<T>* bottomHead;
};

int main()
{
    SkipList<int> skipList;
    for (int j = 0; j < 10; ++j)
    {
        for (int i = 0; i < 10; ++i)
        {
            skipList.insert(i);
        }
        skipList.print();
        cout << endl;

        for (int i = 0; i < 10; ++i)
        {
            skipList.eraseWithHead(i);
            skipList.print();
            cout << endl;
        }
    }

    for (int j = 0; j < 10; ++j)
    {
        for (int i = 0; i < 10; ++i)
        {
            skipList.insert(i);
        }
        skipList.print();
        cout << endl;

        for (int i = 0; i < 10; ++i)
        {
            skipList.erase(i);
            skipList.print();
            cout << endl;
        }
    }


//  for (int i = 0; i < 10; ++i)
//  {
//      Node<int>* p = skipList.search(i);
//      if (p)
//      {
//          cout << "Found" << endl;
//      }
//      else
//      {
//          cout << "Not Found" << endl;
//      }
//  }

    SkipList<string> skipList2;
    skipList2.insert("A");
    skipList2.insert("B");
    skipList2.print();
    skipList2.erase("A");
    skipList2.print();
    skipList2.erase("B");
    skipList2.print();

    return 0;
}

