#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "../DisjSets/DisjSets.h"

using namespace std;

void testDisjSets()
{
    DisjSets ds(8);
    ds.unionSets(4, 5);
    ds.unionSets(6, 7);
    ds.unionSets(4, 6);
    ds.printRoot();
    cout << endl;

    DisjSets ds2(8);
    ds2.unionSetsBySize(4, 5);
    ds2.unionSetsBySize(6, 7);
    ds2.unionSetsBySize(4, 6);
    ds2.unionSetsBySize(3, 4);
    ds2.printRoot();
    cout << endl;

    DisjSets ds3(8);
    ds3.unionSetsByHeight(4, 5);
    ds3.unionSetsByHeight(6, 7);
    ds3.unionSetsByHeight(4, 6);
    ds3.unionSetsByHeight(3, 4);
    ds3.printRoot();
    cout << endl;
}



class Maze
{
public:
    enum Direction{UP = 1, RIGHT = 2, DOWN = 4, LEFT = 8};

    Maze(int r, int c) : row(r), col(c), ds(row * col)
    {
        srand(time(NULL));
        for (int i = 0; i < row; ++i)
        {
            vector<int> tmp(col, 0);
            maze.push_back(tmp);
        }

        //入口和出口
        maze[0][0] = UP; 
        maze[row - 1][col - 1] = DOWN;
    }

    void buildMaze()
    {
        while (!hasPath())
        {
//          print();
//          sleep(1);
            //选定单元格：
            int i = rand() % row;
            int j = rand() % col;
            //随机拆掉一面墙：
            int wall = rand() % 3;
            //墙分割的两个单元格在不相交集中的位置
            int num1 = i * col + j;
            int num2 = 0;
            switch (wall)
            {
            case 0: //上面的墙
                if (!noWall(maze[i][j], UP))
                {
                    if (i > 0)  //最上边一行的墙不能拆
                    {
                        num2 = (i - 1) * col + j;
                        if (isNeedRemoveWall(num1, num2))
                        {
                            maze[i][j] += UP;
                            maze[i - 1][j] += DOWN;
                            ds.unionSetsBySize(num1, num2);
                        }
                    }
                }
                break;
            case 1: //右面的墙
                if (!noWall(maze[i][j], RIGHT))
                {
                    if (j < col - 1)  //最右边一列的墙不能拆
                    {
                        num2 = i * col + j + 1;
                        if (isNeedRemoveWall(num1, num2))
                        {
                            maze[i][j] += RIGHT;
                            maze[i][j + 1] += LEFT;
                            ds.unionSetsBySize(num1, num2);
                        }
                    }
                }
                break;
            case 2: //下面的墙
                if (!noWall(maze[i][j], DOWN))
                {
                    if (i < row - 1)  //最下边一行的墙不能拆
                    {
                        num2 = (i + 1) * col + j;
                        if (isNeedRemoveWall(num1, num2))
                        {
                            maze[i][j] += DOWN;
                            maze[i + 1][j] += UP;
                            ds.unionSetsBySize(num1, num2);
                        }
                    }
                }
                break;
            case 3: //左面的墙
                if (!noWall(maze[i][j], LEFT))
                {
                    if (j > 0)  //最左边一列的墙不能拆
                    {
                        num2 = i * col + j - 1;
                        if (isNeedRemoveWall(num1, num2))
                        {
                            maze[i][j] += LEFT;
                            maze[i][j - 1] += RIGHT;
                            ds.unionSetsBySize(num1, num2);
                        }
                    }
                }
                break;
            }
        }
        int kkk = 1;
    }

    void print()
    {
//      for (int i = 0; i < row; ++i)
//      {
//          for (int j = 0; j < col; ++j)
//          {
//              cout << maze[i][j] << " ";
//          }
//          cout << endl;
//      }
//      cout << endl;

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (i == 0)
                {
                    if (j == 0)
                    {
                        if (noWall(maze[i][j], UP))
                        {
                            cout << "* *";
                        }
                        else
                        {
                            cout << "***";
                        }
                    }
                    else
                    {
                        if (noWall(maze[i][j], UP))
                        {
                            cout << " *";
                        }
                        else
                        {
                            cout << "**";
                        }
                    }
                }
            }
            if (i == 0) 
            {
                cout << endl;
            }

            for (int j = 0; j < col; ++j)
            {
                if (j == 0)
                {
                    if (noWall(maze[i][j], RIGHT))
                    {
                        cout << "*  ";
                    }
                    else
                    {
                        cout << "* *";
                    }
                }
                else
                {
                    if (noWall(maze[i][j], RIGHT))
                    {
                        cout << "  ";
                    }
                    else
                    {
                        cout << " *";
                    }
                }
            }
            cout << endl;

            for (int j = 0; j < col; ++j)
            {
                if (j == 0)
                {
                    if (noWall(maze[i][j], DOWN))
                    {
                        cout << "* *";
                    }
                    else
                    {
                        cout << "***";
                    }
                }
                else
                {
                    if (noWall(maze[i][j], DOWN))
                    {
                        cout << " *";
                    }
                    else
                    {
                        cout << "**";
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }

private:
    bool isNeedRemoveWall(int i, int j)
    {
        return ds.find(i) != ds.find(j);
    }

    bool noWall(int cell, enum Direction dir)
    {
        return cell & dir;
    }

    bool hasPath()
    {
        return ds.find(0) == ds.find(row * col - 1);
    }

    int row;
    int col;
    DisjSets ds;

    /* 
        二维数组元素的值表示当前单元格四周的墙的状态： 
        1：上面没有墙
        2：右面没有墙
        4：下面没有墙
        8：左面没有墙
        多余一面没有墙，用他们的合来表示
    */
    vector<vector<int> > maze;
};


void f()
{
    int tmp = 0;
    for (int i = 0; i < 16; ++i)
    {
        cout << i << ": ";
        tmp = i;
        if (tmp &= 1)
        {
            cout << "1 ";
        }
        tmp = i;
        if (tmp &= 2)
        {
            cout << "2 ";
        }
        tmp = i;
        if (tmp &= 4)
        {
            cout << "4 ";
        }
        tmp = i;
        if (tmp &= 8)
        {
            cout << "8 ";
        }
        cout << endl;
    }
}

int main()
{
    Maze m(3, 3);
    m.buildMaze();
    m.print();

    return 0;
}

