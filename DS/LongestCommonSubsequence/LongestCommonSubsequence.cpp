#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
公共子序列并不一定是连续的
如：ABC和AEBFC的公共子序列是ABC
*/

//递归实现
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

/*动态规划
基本算法：
c[i][j]的定义见下面 
如果x[i]==y[j]，则c[i][j]=max(c[i][j-1],c[i-1][j])+1; 
如果x[i]!=y[j]，则c[i][j]=max(c[i][j-1],c[i-1][j])。 
程序同时需要考虑i或j等于0时的情况。 
*/
int LCS2(const string& x, const string& y)
{
    vector<int> tmp(y.size(), -1);
    //c[i][j]：x的前i个元素和y的前j个元素的最大公共子串长度
    vector<vector<int> > c(x.size(), tmp);

    int i = 0;
    int j = 0;
    for (i = 0; i < x.size(); ++i)
    {
        for (j = 0; j < y.size(); ++j)
        {
            if (-1 == c[i][j])
            {
                //如果x中的字符等于y中的
                if (x[i] == y[j])
                {
                    //如果是起始字符，则公共子串长度为1
                    if (0 == i || 0 == j)
                    {
                        c[i][j] = 1;
                    }
                    //如果不是起始字符，则公共子串等于“之前得出的公共子串长度”+1
                    else
                    {
                        c[i][j] = c[i - 1][j - 1] + 1;
                    }
                }
                else
                {
                    //x是第一个元素，y不是第一个元素，c[i][j]要么是c[i][j-1]（值为1），要么是0
                    if (0 == i && j != 0)
                    {
                        c[i][j] = max(c[i][j - 1], 0);
                    }
                    //x不是第一个元素，y是第一个元素，c[i][j]要么是c[i-1][j]（值为1），要么是0
                    else if (i != 0 && 0 == j)
                    {
                        c[i][j] = max(0, c[i - 1][j]);
                    }
                    //x、y都不是第一个元素，则c[i][j]为c[i][j - 1]和c[i - 1][j]中大的
                    else if (i != 0 && j != 0)
                    {
                        c[i][j] = max(c[i][j - 1], c[i - 1][j]);
                    }
                    //x、y都是第一个元素，则c[i][j]为0
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

//动态规划。在LCS2的基础上，返回最大的子串
int LCS3(const string& x, const string& y, string& maxSub)
{
    vector<int> tmp(y.size(), -1);
    //c[i][j]：x的前i个元素和y的前j个元素的最大公共子串长度
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
                //如果x中的字符等于y中的
                if (x[i] == y[j])
                {
                    //如果是起始字符，则公共子串长度为1
                    if (0 == i || 0 == j)
                    {
                        c[i][j] = 1;
                    }
                    //如果不是起始字符，则公共子串等于“之前得出的公共子串长度”+1
                    else
                    {
                        c[i][j] = c[i - 1][j - 1] + 1;
                    }
                    end = i;
                }
                else
                {
                    //x是第一个元素，y不是第一个元素，c[i][j]要么是c[i][j-1]（值为1），要么是0
                    if (0 == i && j != 0)
                    {
                        c[i][j] = max(c[i][j - 1], 0);
                    }
                    //x不是第一个元素，y是第一个元素，c[i][j]要么是c[i-1][j]（值为1），要么是0
                    else if (i != 0 && 0 == j)
                    {
                        c[i][j] = max(0, c[i - 1][j]);
                    }
                    //x、y都不是第一个元素，则c[i][j]为c[i][j - 1]和c[i - 1][j]中大的
                    else if (i != 0 && j != 0)
                    {
                        c[i][j] = max(c[i][j - 1], c[i - 1][j]);
                    }
                    //x、y都是第一个元素，则c[i][j]为0
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
    //这组值使用递归方法时间太长了，解不出
    //cout << LCS(x2, y2, x2.size() - 1, y2.size() - 1) << endl;
    cout << LCS2(x2, y2) << endl;
    cout << LCS3(x2, y2, maxSub) << ": " << maxSub << endl;

    return 0;
}
