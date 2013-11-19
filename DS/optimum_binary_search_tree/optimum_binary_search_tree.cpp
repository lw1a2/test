#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
    //单词
    string word;
    //出现频率
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

    //打印当前节点
    cout << C[left][right].node.word;

    //打印左节点
    if (C[left][right].l_child.first != -1 && C[left][right].l_child.second != -1)
    {
        cout << "(" << C[C[left][right].l_child.first][C[left][right].l_child.second].node.word
            << ", ";
    }
    else
    {
        cout << "(NULL, ";
    }
    //打印右节点
    if (C[left][right].r_child.first != -1 && C[left][right].r_child.second != -1)
    {
        cout << C[C[left][right].r_child.first][C[left][right].r_child.second].node.word
            << ")" << endl;
    }
    else
    {
        cout << "NULL)" << endl;
    }

    //打印左子树
    printTree(C, C[left][right].l_child.first, C[left][right].l_child.second);
    //打印右子树
    printTree(C, C[left][right].r_child.first, C[left][right].r_child.second);
}

//最优二叉查找树
double f(const vector<Node>& a)
{
    vector<Tree> tmp(a.size());
    //C用来保存子树的频率值
    //例如子树left,i-1的频率值为C[left][i-1]
    vector<vector<Tree> > C(a.size(), tmp);

    //单节点
    for (int left = 0; left < a.size(); ++left)
    {
        C[left][left].node = a[left];
    }

    for (int j = 1; j < a.size(); ++j)
    {
        for (int left = 0; left < a.size() - j; ++left)
        {
            //Pleft到Pright的频率和
            double Pleft_Pright = 0;
            //当根为i时，左子树和右子树的频率和
            double Pchild = 0;
            int i = left;
            int right = left + j;
            for (; i <= right; ++i)
            {
                Pleft_Pright += C[i][i].node.p;
                //左子树的频率和：C[left][i - 1]
                double Pchild_left = 0;
                if (left > i - 1)
                {
                    Pchild_left = 0;
                }
                else
                {
                    Pchild_left = C[left][i - 1].node.p;
                }

                //右子树的频率和：C[i + 1][right]
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

    //打印整个树
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

