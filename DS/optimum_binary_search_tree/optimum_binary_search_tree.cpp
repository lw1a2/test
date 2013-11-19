#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
    //����
    string word;
    //����Ƶ��
    double p;
    Node() : p(0)
    {
    }
};

struct Tree
{
    Node node;
    pair<int, int> l_child;
    pair<int, int> r_child;
    Tree() : l_child(make_pair(-1, -1)), r_child(make_pair(-1, -1))
    {
    }
};

void printTree(const vector<vector<Tree> >& C, int left, int right)
{
    if (-1 == left && -1 == right)
    {
        return;
    }

    //��ӡ��ǰ�ڵ�
    cout << C[left][right].node.word;

    //��ӡ��ڵ�
    if (C[left][right].l_child.first != -1 && C[left][right].l_child.second != -1)
    {
        cout << "(" << C[C[left][right].l_child.first][C[left][right].l_child.second].node.word
            << ", ";
    }
    else
    {
        cout << "(NULL, ";
    }
    //��ӡ�ҽڵ�
    if (C[left][right].r_child.first != -1 && C[left][right].r_child.second != -1)
    {
        cout << C[C[left][right].r_child.first][C[left][right].r_child.second].node.word
            << ")" << endl;
    }
    else
    {
        cout << "NULL)" << endl;
    }

    //��ӡ������
    printTree(C, C[left][right].l_child.first, C[left][right].l_child.second);
    //��ӡ������
    printTree(C, C[left][right].r_child.first, C[left][right].r_child.second);
}

//���Ŷ��������
double f(const vector<Node>& a)
{
    vector<Tree> tmp(a.size());
    //C��������������Ƶ��ֵ
    //��������left,i-1��Ƶ��ֵΪC[left][i-1]
    vector<vector<Tree> > C(a.size(), tmp);

    //���ڵ�
    for (int left = 0; left < a.size(); ++left)
    {
        C[left][left].node = a[left];
    }

    for (int j = 1; j < a.size(); ++j)
    {
        for (int left = 0; left < a.size() - j; ++left)
        {
            //Pleft��Pright��Ƶ�ʺ�
            double Pleft_Pright = 0;
            //����Ϊiʱ������������������Ƶ�ʺ�
            double Pchild = 0;
            int i = left;
            int right = left + j;
            for (; i <= right; ++i)
            {
                Pleft_Pright += C[i][i].node.p;
                //��������Ƶ�ʺͣ�C[left][i - 1]
                double Pchild_left = 0;
                if (left > i - 1)
                {
                    Pchild_left = 0;
                }
                else
                {
                    Pchild_left = C[left][i - 1].node.p;
                }

                //��������Ƶ�ʺͣ�C[i + 1][right]
                double Pchild_right = 0;
                if (i + 1 > right)
                {
                    Pchild_right = 0;
                }
                else
                {
                    Pchild_right = C[i + 1][right].node.p;
                }

                if (0 == Pchild || Pchild > Pchild_left + Pchild_right)
                {
                    Pchild = Pchild_left + Pchild_right;
                    if (left > i - 1)
                    {
                        C[left][right].l_child = (make_pair(-1, -1));
                    }
                    else
                    {
                        C[left][right].l_child = (make_pair(left, i - 1));
                    }
                    if (i + 1 > right)
                    {
                        C[left][right].r_child = (make_pair(-1, -1));
                    }
                    else
                    {
                        C[left][right].r_child = (make_pair(i + 1, right));
                    }
                    C[left][right].node.word = C[i][i].node.word;
                }
            }
            C[left][right].node.p = Pchild + Pleft_Pright;
        }
    }

    //��ӡ������
    printTree(C, 0, a.size() - 1);

    return C[0][a.size() - 1].node.p;
}

int main()
{
    vector<Node> a;

    Node n;

    n.word = "a";
    n.p = 0.22;
    a.push_back(n);

    n.word = "am";
    n.p = 0.18;
    a.push_back(n);

    n.word = "and";
    n.p = 0.20;
    a.push_back(n);

    n.word = "egg";
    n.p = 0.05;
    a.push_back(n);

    n.word = "if";
    n.p = 0.25;
    a.push_back(n);

    n.word = "the";
    n.p = 0.02;
    a.push_back(n);

    n.word = "two";
    n.p = 0.08;
    a.push_back(n);

    cout << f(a) << endl;

    return 0;
}

