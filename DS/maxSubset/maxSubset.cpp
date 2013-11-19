#include "../DisjSets/DisjSets.h"
#include <vector>
#include <iostream>

using namespace std;

/*
�ж�ά����
000000 
011100 
101001 
011101 
000001 
110000 
��������󹫹��Ӽ�����ͼ�Ľ��Ӧ����7 
*/

//ʹ�ò��ཻ��������
int maxSubset(const vector<vector<int> >& v)
{
    if (!v.empty() && !v[0].empty())
    {
        int rows =  v.size();
        int cols =  v[0].size();
        DisjSets ds(rows * cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                //��ÿ��Ԫ�أ������±ߵ�Ԫ�ؽ��бȽϣ������Ƿ�����һ��������
                if (i + 1 < rows
                    && v[i][j] == 1 && v[i + 1][j] == 1)
                {
                    ds.unionSetsBySize(i * cols + j, (i + 1) * cols + j);
                }
                //��ÿ��Ԫ�أ������ұߵ�Ԫ�ؽ��бȽϣ������Ƿ�����һ��������
                if (j + 1 < cols
                    && v[i][j] == 1 && v[i][j + 1] == 1)
                {
                    ds.unionSetsBySize(i * cols + j, i*cols + j + 1);
                }
            }
        }

        //�������size
        int tmp = -1;
        for (int i = 0; i < ds.s.size(); ++i)
        {
            if (ds.s[i] < -1 && tmp > ds.s[i])
            {
                tmp = ds.s[i];
            }
        }
        return 0 - tmp;
    }

    return 0;
}

int main()
{
    vector<int> tmp(6);
    vector<vector<int> > v(6, tmp);

    v[1][1] = 1;
    v[1][2] = 1;
    v[1][3] = 1;
    v[2][0] = 1;
    v[2][2] = 1;
    v[2][5] = 1;
    v[3][1] = 1;
    v[3][2] = 1;
    v[3][3] = 1;
    v[3][5] = 1;
    v[4][5] = 1;
    v[5][0] = 1;
    v[5][1] = 1;

    cout << "MaxSubset: " << maxSubset(v) << endl;

    return 0;
}
