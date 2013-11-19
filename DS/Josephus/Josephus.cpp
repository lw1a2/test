/*
ѭ���������⣺ 
��˵������̫��ʷѧ�� Josephus�й����µĹ��£� 
��������ռ�����������ᣬ39 ����̫����Josephus���������Ѷ㵽һ�����С�
39����̫�˾�����Ը��Ҳ��Ҫ����ץ�������Ǿ�����һ����ɱ��ʽ�� 
41�����ų�һ��ԲȦ���ɵ�1���˿�ʼ������ÿ��������3�˸��˾ͱ�����ɱ�� 
Ȼ��������һ�����±�����ֱ�������˶���ɱ����Ϊֹ��
Ȼ��Josephus ���������Ѳ�������ӣ�JosephusҪ���������ȼ�װ��ӣ� 
�����������Լ������ڵ�16�����31��λ�ã������ӹ����ⳡ������Ϸ�� 
*/
#include <iostream>
#include <list>

using namespace std;

void Josephus(list<int>& l, int m)
{
    list<int>::iterator it = l.begin();
    while (l.size() > 1)
    {
        for (int i = 1; i <= m && l.size() > 1; ++i)
        {
            if (it == l.end())
            {
                it = l.begin();
            }
            ++it;
        }
        if (it == l.end())
        {
            it = l.begin();
        }
        l.erase(it++);
    }
}

int main()
{
    list<int> l;
    for (int i = 1; i <= 5; ++i)
    {
        l.push_back(i);
    }

    Josephus(l, 0);

    for (list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << endl;
    }

    l.clear();

    for (int i = 1; i <= 100000; ++i)
    {
        l.push_back(i);
    }

    Josephus(l, 1);

    for (list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << endl;
    }

    l.clear();

    return 0;
}

