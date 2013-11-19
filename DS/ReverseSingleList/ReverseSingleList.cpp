#include <iostream>

using namespace std;

struct Node
{
    int i;
    Node* next;
};

void ReverseSingleList(Node*& head)
{
    Node* p = head, *tmp = NULL;
    Node *p2 = NULL;    //新链表
    while (p)
    {
        //从旧链表的表头取下来
        tmp = p;
        p = p->next;

        //接到新链表的表头
        tmp->next = p2;
        p2 = tmp;
    }

    head = p2;
}

int main()
{
    Node *p = new Node, *p2 = NULL;
    p->i = 1;
    p->next = NULL;
    p2 = p;

    p = new Node;
    p->i = 2;
    p->next = p2;
    p2 = p;

     p = new Node;
    p->i = 3;
    p->next = p2;

    Node *head = p;
    while (p)
    {
        cout << p->i << endl;
        p = p->next;
    }
    cout << endl;

    ReverseSingleList(head);
    p = head;
    while (p)
    {
        cout << p->i << endl;
        p = p->next;
    }

    return 0;
}
