#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int v;
    Node* l;
    Node* r;
    Node() : v(-1), l(NULL), r(NULL)
    {
    }
};

enum Tag {L, R};

struct StackNode
{
    Node* p;
    Tag tag;
};

//�ݹ�
void TraverseTreePostOrder(Node* root)
{
    if (!root)
    {
        return;
    }

    TraverseTreePostOrder(root->l);
    TraverseTreePostOrder(root->r);
    cout << root->v << endl;
}

//�ǵݹ�
void TraverseTreePostOrder2(Node* root)
{
    if (!root)
    {
        return;
    }

    stack<StackNode> s;
    Node* p = root;
    StackNode x;
    do   
    {
        //����������ջ
        while (p)                     
        {
            x.p = p;   
            x.tag = L;
            s.push(x);
            p = p->l;
        }

        while (!s.empty() && s.top().tag == R)
        {
            x = s.top();
            s.pop(); 
            p = x.p; 
            cout << p->v << endl;     //tagΪR����ʾ������������ϣ��ʷ��ʸ����               
        } 

        //���������� 
        if (!s.empty())
        {
            s.top().tag = R;        
            p = s.top().p->r;                 
        }
    } while (!s.empty()); 
}

int main()
{
    Node* root = new Node;
    root->v = 0;

    Node* p = new Node;
    p->v = 1;
    root->l = p;

    p = new Node;
    p->v = 3;
    root->r = p;

    p = new Node;
    p->v = 2;
    root->l->l = p;

    p = new Node;
    p->v = 5;
    root->l->l->r = p;

    p = new Node;
    p->v = 4;
    root->l->r = p;

    p = new Node;
    p->v = 6;
    root->l->r->r = p;

    TraverseTreePostOrder(root);

    cout << endl;

    TraverseTreePostOrder2(root);

    return 0;
}

