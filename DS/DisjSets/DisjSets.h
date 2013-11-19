#pragma once

#include <vector>
#include <iostream>

class DisjSets
{
public:
    explicit DisjSets(int num) : s(num, -1)
    {
    }

    //任意求并
    void unionSets(int i, int j)
    {
        int root1 = find(i);
        int root2 = find(j);
        if (root1 != root2)
        {
            s[root2] = root1;
        }
    }

    //按树的大小求并，小的树成为大的树的子树
    //根为树的大小的相反数
    void unionSetsBySize(int i, int j)
    {
        int root1 = find(i);
        int root2 = find(j);
        if (root1 != root2)
        {
            int size1 = -s[root1];
            int size2 = -s[root2];
            if (size1 >= size2)
            {
                s[root1] = -(size1 + size2);
                s[root2] = root1;
            }
            else
            {
                s[root2] = -(size1 + size2);
                s[root1] = root2;
            }
        }
    }

    //按树的高度求并，浅的树成为深的树的子树
    //根为树的高度的相反数再减1
    void unionSetsByHeight(int i, int j)
    {
        int root1 = find(i);
        int root2 = find(j);
        if (root1 != root2)
        {
            int height1 = 0 - s[root1] - 1;
            int height2 = 0 - s[root2] - 1;
            if (height1 >= height2)
            {
                if (height1 == height2)
                {
                    --s[root1];
                }
                s[root2] = root1;
            }
            else
            {
                if (height1 == height2)
                {
                    --s[root2];
                }
                s[root1] = root2;
            }
        }
    }

    int find(int x) const
    {
        while (s[x] >= 0)
        {
            x = s[x];
        }
        return x;
    }

    //路径压缩：find操作后，从x到根的路径上的每一个结点都使它的父节点变成根
    int find(int x)
    {
        if (s[x] < 0)
        {
            return x;
        }

        return s[x] = find(s[x]);
    }

    int printRoot() const
    {
        for (int i = 0; i < s.size(); ++i)
        {
            std::cout << i << ": " << s[i] << std::endl;
        }
    }

    std::vector<int> s;
};

