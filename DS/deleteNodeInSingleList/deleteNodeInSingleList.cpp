//ʹ�õ�ǰ�ڵ��ָ�룬ɾ��������Ķ���

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

    //����һ�������ݸ��ǵ�ǰ������
    tmp = p_del->next;
    memcpy(p_del, p_del->next, sizeof(Node));
    //������һ�����ڴ��ͷŵ�
    delete tmp;

    print(p);

    return 0;
}

