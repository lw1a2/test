#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
���������в���һ����������
�磺ABC��AEBFC�Ĺ�����������ABC
*/

//�ݹ�ʵ��
int LCS(const string& x, const string& y, int i, int j)
{
    if (0 == i)
    {
        for (int k = 0; k <= j; ++k)
        {
            if (x[i] == y[k])
            {
                return 1;
            }
        }
    }
    else if (0 == j)
    {
        for (int k = 0; k <= i; ++k)
        {
            if (x[k] == y[j])
            {
                return 1;
            }
        }
    }

    if (0 == i || 0 == j)
    {
        return 0;
    }

    if (x[i] == y[j])
    {
        return LCS(x, y, i - 1, j - 1) + 1;
    }
    else
    {
        return max(LCS(x, y, i, j - 1), LCS(x, y, i - 1, j));
    }
}

/*��̬�滮
�����㷨��
c[i][j]�Ķ�������� 
���x[i]==y[j]����c[i][j]=max(c[i][j-1],c[i-1][j])+1; 
���x[i]!=y[j]����c[i][j]=max(c[i][j-1],c[i-1][j])�� 
����ͬʱ��Ҫ����i��j����0ʱ������� 
*/
int LCS2(const string& x, const string& y)
{
    vector<int> tmp(y.size(), -1);
    //c[i][j]��x��ǰi��Ԫ�غ�y��ǰj��Ԫ�ص���󹫹��Ӵ�����
    vector<vector<int> > c(x.size(), tmp);

    int i = 0;
    int j = 0;
    for (i = 0; i < x.size(); ++i)
    {
        for (j = 0; j < y.size(); ++j)
        {
            if (-1 == c[i][j])
            {
                //���x�е��ַ�����y�е�
                if (x[i] == y[j])
                {
                    //�������ʼ�ַ����򹫹��Ӵ�����Ϊ1
                    if (0 == i || 0 == j)
                    {
                        c[i][j] = 1;
                    }
                    //���������ʼ�ַ����򹫹��Ӵ����ڡ�֮ǰ�ó��Ĺ����Ӵ����ȡ�+1
                    else
                    {
                        c[i][j] = c[i - 1][j - 1] + 1;
                    }
                }
                else
                {
                    //x�ǵ�һ��Ԫ�أ�y���ǵ�һ��Ԫ�أ�c[i][j]Ҫô��c[i][j-1]��ֵΪ1����Ҫô��0
                    if (0 == i && j != 0)
                    {
                        c[i][j] = max(c[i][j - 1], 0);
                    }
                    //x���ǵ�һ��Ԫ�أ�y�ǵ�һ��Ԫ�أ�c[i][j]Ҫô��c[i-1][j]��ֵΪ1����Ҫô��0
                    else if (i != 0 && 0 == j)
                    {
                        c[i][j] = max(0, c[i - 1][j]);
                    }
                    //x��y�����ǵ�һ��Ԫ�أ���c[i][j]Ϊc[i][j - 1]��c[i - 1][j]�д��
                    else if (i != 0 && j != 0)
                    {
                        c[i][j] = max(c[i][j - 1], c[i - 1][j]);
                    }
                    //x��y���ǵ�һ��Ԫ�أ���c[i][j]Ϊ0
                    else
                    {
                        c[i][j] = 0;
                    }
                }
            }
        }
    }

    return c[x.size() - 1][y.size() - 1];
}

//��̬�滮����LCS2�Ļ����ϣ����������Ӵ�
int LCS3(const string& x, const string& y, string& maxSub)
{
    vector<int> tmp(y.size(), -1);
    //c[i][j]��x��ǰi��Ԫ�غ�y��ǰj��Ԫ�ص���󹫹��Ӵ�����
    vector<vector<int> > c(x.size(), tmp);
    int end = 0;

    int i = 0;
    int j = 0;
    for (i = 0; i < x.size(); ++i)
    {
        for (j = 0; j < y.size(); ++j)
        {
            if (-1 == c[i][j])
            {
                //���x�е��ַ�����y�е�
                if (x[i] == y[j])
                {
                    //�������ʼ�ַ����򹫹��Ӵ�����Ϊ1
                    if (0 == i || 0 == j)
                    {
                        c[i][j] = 1;
                    }
                    //���������ʼ�ַ����򹫹��Ӵ����ڡ�֮ǰ�ó��Ĺ����Ӵ����ȡ�+1
                    else
                    {
                        c[i][j] = c[i - 1][j - 1] + 1;
                    }
                    end = i;
                }
                else
                {
                    //x�ǵ�һ��Ԫ�أ�y���ǵ�һ��Ԫ�أ�c[i][j]Ҫô��c[i][j-1]��ֵΪ1����Ҫô��0
                    if (0 == i && j != 0)
                    {
                        c[i][j] = max(c[i][j - 1], 0);
                    }
                    //x���ǵ�һ��Ԫ�أ�y�ǵ�һ��Ԫ�أ�c[i][j]Ҫô��c[i-1][j]��ֵΪ1����Ҫô��0
                    else if (i != 0 && 0 == j)
                    {
                        c[i][j] = max(0, c[i - 1][j]);
                    }
                    //x��y�����ǵ�һ��Ԫ�أ���c[i][j]Ϊc[i][j - 1]��c[i - 1][j]�д��
                    else if (i != 0 && j != 0)
                    {
                        c[i][j] = max(c[i][j - 1], c[i - 1][j]);
                    }
                    //x��y���ǵ�һ��Ԫ�أ���c[i][j]Ϊ0
                    else
                    {
                        c[i][j] = 0;
                    }
                }
            }
        }
    }

    maxSub = x.substr(end - c[x.size() - 1][y.size() - 1] - 1, c[x.size() - 1][y.size() - 1]);
    return c[x.size() - 1][y.size() - 1];
}

int main()
{
    string x("ABCBDABDABDACDABCDABCD");
    string y("BDCCBADBBDACDABCDADBDB");
    string maxSub;
    cout << LCS(x, y, x.size() - 1, y.size() - 1) << endl;
    cout << LCS2(x, y) << endl;
    cout << LCS3(x, y, maxSub) << ": " << maxSub << endl;

    string x2("ABCBDABDABDACDABCDABCDCADBCDABCABCD");
    string y2("BDCCBADBBDACDABCDADBDBCDABBCDAACDADABA");
    //����ֵʹ�õݹ鷽��ʱ��̫���ˣ��ⲻ��
    //cout << LCS(x2, y2, x2.size() - 1, y2.size() - 1) << endl;
    cout << LCS2(x2, y2) << endl;
    cout << LCS3(x2, y2, maxSub) << ": " << maxSub << endl;

    return 0;
}
