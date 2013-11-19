/*
循环报数问题： 
据说著名犹太历史学家 Josephus有过以下的故事： 
在罗马人占领乔塔帕特後，39 个犹太人与Josephus及他的朋友躲到一个洞中。
39个犹太人决定宁愿死也不要被人抓到，于是决定了一个自杀方式。 
41个人排成一个圆圈，由第1个人开始报数，每报数到第3人该人就必须自杀， 
然后再由下一个重新报数，直到所有人都自杀身亡为止。
然而Josephus 和他的朋友并不想遵从，Josephus要他的朋友先假装遵从， 
他将朋友与自己安排在第16个与第31个位置，于是逃过了这场死亡游戏。 
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

