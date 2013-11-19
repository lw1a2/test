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

    if (p.size() == j)              //j�������˵���ҵ���
    {
        return i - p.size();
    }

    return string::npos;
}

string::size_type kmp3(const string& t, const string& p)
{
    //next[i]����0��iǰ���ֺͺ󲿷ֵ�"��󹫹�����"
    //�磬p=abacaba����next[6]=3��ֵΪaba��
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
            if (j == 0) i++;        //��jΪ��һ��Ԫ�أ������i��j����
            else j = next[j - 1];   //j֮ǰ�м����ظ���Ԫ�أ�����������
        }
    }

    if (p.size() == j)              //j�������˵���ҵ���
    {
        return i - p.size();
    }

    return string::npos;
}

//Ŀǰ���������ķ���
string::size_type kmp5(const string& t, const string& p)
{
    //next[i]��p[0..i]��ǰ���ֺͺ󲿷ֵ�"��󹫹�����"
    //�磬p=abacaba����next[6]=3��ֵΪaba��
    vector<string::size_type> next(p.size(), 0);  
    //next[0]ʼ��Ϊ0
    for (string::size_type i = 1; i < p.size(); ++i)
    {
        int len = next[i - 1];  //p[0..i-1]�Ĺ������ֵĳ���
        int index = len;        //p[0..i-1]�Ĺ��������Ҳ��1λ    
        //��p[index] != p[i]
        //����len=next[index]�������Ƚ�p[index]��p[i]
        while (p[index] != p[i] && len > 0)   
        {
            len = next[index];  //����ط������е��ƣ�������ע��
            index = len;
        }
        if (p[index] == p[i]) next[i] = len + 1;
        else next[i] = 0;
    }

    string::size_type i = 0, j = 0;
    while (i < p.size() && j < t.size())
    {
        if (p[i] == t[j])           //������򶼵���
        {
            ++i; ++j;
        }
        else
        {
            if (i == 0) j++;        //��iΪ��һ��Ԫ�أ������j��i����
            else i = next[i - 1];   //i֮ǰ�м����ظ���Ԫ�أ�����������
        }
    }

    if (p.size() == i)              //i�������˵���ҵ���
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

