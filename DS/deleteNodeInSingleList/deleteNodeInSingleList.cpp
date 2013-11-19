//使用当前节点的指针，删除单链表的对象

#include <iostream>
#include <cstring>

using namespace std;

struct Node
{
    int v;
    Node* next;
};

void print(const Node* p)
{
    while(p)
    {
        cout << p->v << endl;
        p = p->next;
    }
}

int main()
{
    Node *p = NULL, *tmp = NULL, *p_del = NULL;
    p = new Node;
    p->v = 1;
    p->next = NULL;
    tmp = p;
    p = new Node;
    p->v = 2;
    p->next = tmp;
    p_del = p;
    tmp = p;
    p = new Node;
    p->v = 3;
    p->next = tmp;
    tmp = p;
    p = new Node;
    p->v = 4;
    p->next = tmp;

    print(p);

    //用下一个的数据覆盖当前的数据
    tmp = p_del->next;
    memcpy(p_del, p_del->next, sizeof(Node));
    //并把下一个的内存释放掉
    delete tmp;

    print(p);

    return 0;
}

