#include <iostream>
#include <string>
#include <vector>

using namespace std;

string::size_type naive(const string& t, const string& p)
{
    string::size_type pos = 0;
    bool match = false;
    for (string::size_type i = 0; i < t.size(); ++i)
    {
        for (string::size_type j = 0; j < p.size(); ++j)
        {
            if (t[i + j] != p[j])
            {
                match = false;
                break;
            }
            else
            {
                match = true;
            }
        }
        if (match)
        {
            return i;
        }
    }

    return string::npos;
}

string::size_type kmp(const string& t, const string& p)
{
    vector<string::size_type> next(p.size());
    if (!next.empty())
    {
        next[0] = -1;
        for (string::size_type i = 1; i < p.size(); ++i)
        {
            int k = next[i - 1];
            while (p[k + 1] != p[i] && k >= 0)
            {
                k = next[k];
            }
            if (p[k + 1] == p[i]) next[i] = k + 1;
            else next[i] = -1;
        }
    }

    string::size_type i = 0, j = 0;
    while (i < t.size() && j < p.size())
    {
        if (t[i] == p[j])
        {
            ++i; ++j;
        }
        else
        {
            if (j == 0) i++;
            else j = next[j - 1] + 1;
        }
    }

    if (p.size() == j)              //j到达最后，说明找到了
    {
        return i - p.size();
    }

    return string::npos;
}

string::size_type kmp3(const string& t, const string& p)
{
    //next[i]：从0到i前部分和后部分的"最大公共长度"
    //如，p=abacaba，则next[6]=3（值为aba）
    vector<string::size_type> next(p.size(), 0);
    string::size_type k = 0;
    for (string::size_type q = 1; q < p.size(); ++q)
    {
        while (k > 0 && p[k] != p[q])
        {
            k = next[k];
        }
        if (p[k] == p[q])
        {
            ++k;
        }
        next[q] = k;
    }

    string::size_type i = 0, j = 0;
    while (i < t.size() && j < p.size())
    {
        if (t[i] == p[j])
        {
            ++i; ++j;
        }
        else
        {
            if (j == 0) i++;        //若j为第一个元素，则递增i，j不变
            else j = next[j - 1];   //j之前有几个重复的元素，就跳过几个
        }
    }

    if (p.size() == j)              //j到达最后，说明找到了
    {
        return i - p.size();
    }

    return string::npos;
}

//目前最容易理解的方法
string::size_type kmp5(const string& t, const string& p)
{
    //next[i]：p[0..i]的前部分和后部分的"最大公共长度"
    //如，p=abacaba，则next[6]=3（值为aba）
    vector<string::size_type> next(p.size(), 0);  
    //next[0]始终为0
    for (string::size_type i = 1; i < p.size(); ++i)
    {
        int len = next[i - 1];  //p[0..i-1]的公共部分的长度
        int index = len;        //p[0..i-1]的公共部分右侧的1位    
        //若p[index] != p[i]
        //则让len=next[index]，继续比较p[index]和p[i]
        while (p[index] != p[i] && len > 0)   
        {
            len = next[index];  //这个地方还是有点绕，待补充注释
            index = len;
        }
        if (p[index] == p[i]) next[i] = len + 1;
        else next[i] = 0;
    }

    string::size_type i = 0, j = 0;
    while (i < p.size() && j < t.size())
    {
        if (p[i] == t[j])           //若相等则都递增
        {
            ++i; ++j;
        }
        else
        {
            if (i == 0) j++;        //若i为第一个元素，则递增j，i不变
            else i = next[i - 1];   //i之前有几个重复的元素，就跳过几个
        }
    }

    if (p.size() == i)              //i到达最后，说明找到了
    {
        return j - p.size();
    }

    return string::npos;
}

void f(const string& t, const string& p)
{
    cout << "------------------------" << endl;
    string::size_type pos = 0;

    pos = naive(t, p);
    if (string::npos == pos)
    {
        cout << "Not Found" << endl;
    }
    else
    {
        cout << pos << endl;
    }

    pos = kmp(t, p);
    if (string::npos == pos)
    {
        cout << "Not Found" << endl;
    }
    else
    {
        cout << pos << endl;
    }

    pos = kmp3(t, p);
    if (string::npos == pos)
    {
        cout << "Not Found" << endl;
    }
    else
    {
        cout << pos << endl;
    }

    pos = kmp5(t, p);
    if (string::npos == pos)
    {
        cout << "Not Found" << endl;
    }
    else
    {
        cout << pos << endl;
    }
}

int main()
{
    f("ababacababab", "ababab");
    f("abcabcabdabba", "abcabd");
    f("abacabad", "abacabab");
    f("bacbababacabcbab", "ababaca");
    f("bbb", "bb");

    return 0;
}

