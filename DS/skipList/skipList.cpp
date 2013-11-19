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
        //在头结点插入最小值
        topHead = bottomHead = new Node<T>;
    }

    Node<T>* search(const T& value)
    {
        //从最高的链开始查找
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
                    //回退一个节点
                    p = p->prev;
                    //向下走
                    if (p)
                    {
                        p = p->down;
                    }
                }
            }
            //这一层都没找到，则下降一层
            if (prev->down)
            {
                p = prev->down;
            }
        }

        return NULL;
    }

    void insert(const T& value)
    {
        //从最低的链找到插入位置，插入
        Node<T>* newNode = insertIntoList(bottomHead, value);

        //是否需要加入到高的链中
        int coin = rand();
        Node<T>* p = bottomHead;
        Node<T>* newNodeHighLevel = NULL;
        while (coin % 2)
        {
            //加入到更高的链中
            if (p->up)
            {
                newNodeHighLevel = insertIntoList(p->up, value);
            }
            else
            {
                //没有更高的链，则把当前链的第一个节点提升，形成新链
                Node<T>* head = new Node<T>;    //在头结点插入最小值
                head->down = p;
                p->up = head;
                topHead = head;
                //把新节点插入到新链中
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

            //整链为空，则删除多余的头结点（最后一链的topHead和bottomHead会保留）
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
                //回退一个节点
                p = p->prev;
                //把新节点加入到链表中
                newNode->next = p->next;
                p->next = newNode;
                newNode->prev = newNode->next->prev;
                newNode->next->prev = newNode;
                return newNode;
            }
        }
        //链表中找不到位置
        if (!p)
        {
            if (prev)   //链表不为空，就添加到结尾
            {
                prev->next = newNode;
                newNode->prev = prev;
            }
            else        //链表一开始就是空的
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

