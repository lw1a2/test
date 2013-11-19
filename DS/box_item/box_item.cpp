#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

void f(const vector<int>& items, int C, vector<int>& boxs)
{
    for (vector<int>::const_iterator item = items.begin(); item != items.end(); ++item)
    {
        bool packed = false;
        for (vector<int>::iterator box = boxs.begin(); box != boxs.end(); ++box)
        {
            if (*box + *item <= C)
            {
                *box += *item;
                packed = true;
                break;
            }
        }
        if (!packed)
        {
            boxs.push_back(*item);
        }
    }
}

void f2(const vector<int>& items, int C, priority_queue<int, vector<int>, greater<int> >& boxs)
{
    for (vector<int>::const_iterator item = items.begin(); item != items.end(); ++item)
    {
        if (!boxs.empty())
        {
            int tmp = boxs.top();
            if (tmp + *item <= C)
            {
                tmp += *item;
                boxs.pop();
                boxs.push(tmp);
            }
            else
            {
                boxs.push(*item);
            }
        }
        else
        {
            boxs.push(*item);
        }
    }
}

struct box3
{
    int weight;
    int quantity;
    bool operator<(const box3& rhs) const
    {
        return quantity < rhs.quantity;
    }
};

void f3(const vector<int>& items, int C, multiset<box3>& boxs)
{
    for (vector<int>::const_iterator item = items.begin(); item != items.end(); ++item)
    {
        bool packed = false;
        for (multiset<box3>::iterator box = boxs.begin(); box != boxs.end(); ++box)
        {
            if (box->weight + *item <= C)
            {
                box3 tmp;
                tmp.weight = box->weight + *item;
                tmp.quantity = box->quantity + 1;
                boxs.erase(box);
                boxs.insert(tmp);
                packed = true;
                break;
            }
        }
        if (!packed)
        {
            box3 tmp;
            tmp.weight = *item;
            tmp.quantity = 1;
            boxs.insert(tmp);
        }
    }
}

int main()
{
    vector<int> items;
    items.push_back(2);
    items.push_back(2);
    items.push_back(3);
    items.push_back(3);

    vector<int> boxs;
    f(items, 5, boxs);
    cout << boxs.size() << endl;

    priority_queue<int, vector<int>, greater<int> > boxs2;
    f2(items, 5, boxs2);
    cout << boxs2.size() << endl;

    multiset<box3> boxs3;
    f3(items, 5, boxs3);
    cout << boxs3.size() << endl;

    return 0;
}

