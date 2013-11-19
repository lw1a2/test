#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <queue>

using namespace std;

const int INFINITE = 9999999;

struct VertexWeighted;
struct Vertex
{
    Vertex(const string& n, int in) 
        : name(n), indegree(in), output(false), known(false), dist(INFINITE), path(NULL)
                                        
    {
    }

    void insertAdj(Vertex* adj)
    {
        adjTbl.push_back(adj);
    }

    vector<Vertex*> adjTbl;
    int indegree;
    string name;
    bool output;
    bool known;
    int dist;
    Vertex* path;

    //加权的邻接顶点
    vector<VertexWeighted> adjWeightedTbl;
    void insertWeightedAdj(const VertexWeighted& adj)
    {
        adjWeightedTbl.push_back(adj);
    }
};

struct VertexWeighted
{
    Vertex* vertex;
    int weight;
};

class Graph
{
public:
    Graph(const vector<Vertex*>& _vertexs): vertexs(_vertexs)
    {
        
    }

    ~Graph()
    {
        for (int i = 0; i < vertexs.size(); ++i)
        {
            delete vertexs[i];
        }
    }

    //拓扑排序方法1：时间复杂度为|V|^2
    void topoSort()
    {
        for (int i = 0; i < vertexs.size(); ++i)
        {
            for (int k = 0; k < vertexs.size(); ++k)
            {
                if (!vertexs[k]->output && 0 == vertexs[k]->indegree)
                {
                    cout << vertexs[k]->name << " ";
                    for (int j = 0; j < vertexs[k]->adjTbl.size(); ++j)
                    {
                        --(vertexs[k]->adjTbl[j]->indegree);
                    }
                    vertexs[k]->output = true;
                }
            }
        }
        cout << endl;
    }

    //拓扑排序方法2：时间复杂度为|E|+|V|
    void topoSort2()
    {
        queue<Vertex*> vertexWithZeroInDegree;
        for (int i = 0; i < vertexs.size(); ++i)
        {
            if (0 == vertexs[i]->indegree)
            {
                vertexWithZeroInDegree.push(vertexs[i]);
            }
        }

        while (!vertexWithZeroInDegree.empty())
        {
            Vertex* tmp = vertexWithZeroInDegree.front();
            cout << tmp->name << " ";
            for (int j = 0; j < tmp->adjTbl.size(); ++j)
            {
                --(tmp->adjTbl[j]->indegree);
                if (0 == tmp->adjTbl[j]->indegree)
                {
                    vertexWithZeroInDegree.push(tmp->adjTbl[j]);
                }
            }
            vertexWithZeroInDegree.pop();
        }
        cout << endl;
    }

    void unweighted(int vertex)
    {
        vertexs[vertex - 1]->dist = 0;

        for (int currDist = 0; currDist < vertexs.size(); ++currDist)
        {
            for (int j = 0; j < vertexs.size(); ++j)
            {
                Vertex* v = vertexs[j];
                if (!v->known && v->dist == currDist)
                {
                    v->known = true;
                    for (int i = 0; i < v->adjTbl.size(); ++i)
                    {
                        if (INFINITE == v->adjTbl[i]->dist)
                        {
                            v->adjTbl[i]->dist = currDist + 1; 
                            v->adjTbl[i]->path = v;
                        }
                    }
                }
            }
        }
    }

    void unweighted2(int vertex)
    {
        vertexs[vertex - 1]->dist = 0;

        queue<Vertex*> currDistQueue;
        currDistQueue.push(vertexs[vertex - 1]);

        for (int currDist = 0; currDist < vertexs.size(); ++currDist)
        {
            queue<Vertex*> nextDistQueue;
            while (!currDistQueue.empty())
            {
                Vertex* v = currDistQueue.front();
                v->known = true;
                for (int i = 0; i < v->adjTbl.size(); ++i)
                {
                    if (INFINITE == v->adjTbl[i]->dist)
                    {
                        v->adjTbl[i]->dist = currDist + 1; 
                        v->adjTbl[i]->path = v;
                        nextDistQueue.push(v->adjTbl[i]);
                    }
                }
                currDistQueue.pop();
            }
            currDistQueue = nextDistQueue;
        }
    }

    void unweighted3(int vertex)
    {
        vertexs[vertex - 1]->dist = 0;

        queue<Vertex*> distQueue;
        distQueue.push(vertexs[vertex - 1]);

        while (!distQueue.empty())
        {
            Vertex* v = distQueue.front();
            for (int i = 0; i < v->adjTbl.size(); ++i)
            {
                if (INFINITE == v->adjTbl[i]->dist)
                {
                    v->adjTbl[i]->dist = v->dist + 1; 
                    v->adjTbl[i]->path = v;
                    distQueue.push(v->adjTbl[i]);
                }
            }
            distQueue.pop();
        }
    }

    void printPath()
    {
        //输出最短路径
        for (int i = 0; i < vertexs.size(); ++i)
        {
            cout << vertexs[i]->name << "(" << vertexs[i]->dist << "):";
            string path;
            Vertex* p = vertexs[i];
            while (p)
            {
                path = " " + p->name + path;
                p = p->path;
            }
            cout << path << endl;
        }
    }

    void dijkstra(int vertex)
    {
        vertexs[vertex - 1]->dist = 0;

        Vertex* v = vertexs[vertex - 1];
        
        while (1)
        {
            //更新邻接表的dist
            for (int i = 0; i < v->adjWeightedTbl.size(); ++i)
            {
                if (!v->adjWeightedTbl[i].vertex->known 
                    && v->adjWeightedTbl[i].vertex->dist > v->dist + v->adjWeightedTbl[i].weight)
                {
                    v->adjWeightedTbl[i].vertex->dist = v->dist + v->adjWeightedTbl[i].weight;
                    v->adjWeightedTbl[i].vertex->path = v;
                }
            }

            //选出最小的unknown顶点
            v->known = true;
            Vertex* minDistV = NULL;
            for (int i = 0; i < vertexs.size(); ++i)
            {
                if (!vertexs[i]->known 
                    && (NULL == minDistV || minDistV->dist > vertexs[i]->dist))
                {
                    minDistV = vertexs[i];
                }
            }
            
            //当所有顶点都为known时，结束
            if (NULL == minDistV)
            {
                break;
            }
            v = minDistV;
        }
    }

    void weightedNegative(int vertex)
    {
        vertexs[vertex - 1]->dist = 0;
        set<Vertex*> q;
        q.insert(vertexs[vertex - 1]);

        while (!q.empty())
        {
            //更新邻接表的dist
            Vertex* v = *q.begin();
            q.erase(q.begin());
            for (int i = 0; i < v->adjWeightedTbl.size(); ++i)
            {
                if (v->adjWeightedTbl[i].vertex->dist > v->dist + v->adjWeightedTbl[i].weight)
                {
                    v->adjWeightedTbl[i].vertex->dist = v->dist + v->adjWeightedTbl[i].weight;
                    v->adjWeightedTbl[i].vertex->path = v;

                    //只要dist减小了，则这个顶点的邻接顶点都需要重新调整
                    q.insert(v->adjWeightedTbl[i].vertex);
                }
            }
        }
    }

    void criticalPath(int vertex)
    {
        for (int i = 0; i < vertexs.size(); ++i)
        {
            vertexs[i]->dist = 0;
        }

        vertexs[vertex - 1]->dist = 0;
        queue<Vertex*> q;
        q.push(vertexs[vertex - 1]);

        while (!q.empty())
        {
            //更新邻接表的dist
            Vertex* v = q.front();
            q.pop();
            Vertex* criticalVertex = NULL;
            for (int i = 0; i < v->adjWeightedTbl.size(); ++i)
            {
                --v->adjWeightedTbl[i].vertex->indegree;
                //dist为它的入边中，权大的
                if (v->adjWeightedTbl[i].vertex->dist < v->dist + v->adjWeightedTbl[i].weight)
                {
                    v->adjWeightedTbl[i].vertex->dist = v->dist + v->adjWeightedTbl[i].weight;
                    v->adjWeightedTbl[i].vertex->path = v;
                }
                if (0 == v->adjWeightedTbl[i].vertex->indegree)
                {
                    q.push(v->adjWeightedTbl[i].vertex);
                }
            }
        }
    }

    void printCriticalPath()
    {
        //输出关键路径
        Vertex* v = vertexs[vertexs.size() - 1];
        string criticalPath;
        while (v)
        {
            if (criticalPath != "")
            {
                criticalPath = v->name + "->" + criticalPath;
            }
            else
            {
                criticalPath = v->name;
            }
            v = v->path;
        }
        cout << criticalPath << ": " << vertexs[vertexs.size() - 1]->dist << endl;
    }

    void networkStream()
    {
//方法一：未找出答案
//      for (int i = 0; i < vertexs.size(); ++i)
//      {
//          vertexs[i]->dist = 0;
//      }
//
//      Vertex* v = vertexs[0];
//
//      for (int j = 0; j < 2; ++j)
//      {
//          int minStream = INFINITE;
//          while (v)
//          {
//              int maxWeight = 0;
//              Vertex* maxDistV = NULL;
//              //选出最大的邻接顶点
//              for (int i = 0; i < v->adjWeightedTbl.size(); ++i)
//              {
//                  if (maxWeight < v->adjWeightedTbl[i].weight)
//                  {
//                      maxWeight = v->adjWeightedTbl[i].weight;
//                      maxDistV = v->adjWeightedTbl[i].vertex;
//                      v->adjWeightedTbl[i].vertex->path = v;
//                  }
//              }
//
//              if (maxDistV != NULL && minStream > maxWeight)
//              {
//                  minStream = maxWeight;
//              }
//
//              v = maxDistV;
//          }
//
//          printNetworkStream(minStream);
//
//          Vertex* p = vertexs[vertexs.size() - 1];
//          while (p)
//          {
//              Vertex* tmp = p->path;
//              if (tmp)
//              {
//                  for (vector<VertexWeighted>::iterator it = tmp->adjWeightedTbl.begin();
//                       it != tmp->adjWeightedTbl.end(); ++it)
//                  {
//                      if (p == it->vertex)
//                      {
//                          it->weight -= minStream;
//                          if (0 == it->weight)
//                          {
//                              tmp->adjWeightedTbl.erase(it);
//                          }
//                          break;
//                      }
//                  }
//              }
//              p = tmp;
//          }
//
//      }

//方法二：未找出答案
//      //参考习题9.14的答案，其中dist即为fi
//      for (int i = 0; i < vertexs.size(); ++i)
//      {
//          vertexs[i]->dist = 0;
//      }
//      vertexs[0]->dist = INFINITE;
//
//      Vertex* v = vertexs[0];
//      while (1)
//      {
//          Vertex* maxDistV = NULL;
//          //选出dist最大的unknown顶点
//          for (int i = 0; i < vertexs.size(); ++i)
//          {
//              if (!vertexs[i]->known
//                  && (NULL == maxDistV || maxDistV->dist < vertexs[i]->dist))
//              {
//                  maxDistV = vertexs[i];
//              }
//          }
//          //当所有顶点都为known时，结束
//          if (NULL == maxDistV)
//          {
//              break;
//          }
//
//          for (int i = 0; i < maxDistV->adjWeightedTbl.size(); ++i)
//          {
//              int cost = min(maxDistV->dist, maxDistV->adjWeightedTbl[i].weight);
//              if (cost > maxDistV->adjWeightedTbl[i].vertex->dist)
//              {
//                  maxDistV->adjWeightedTbl[i].vertex->dist = cost;
//                  maxDistV->adjWeightedTbl[i].vertex->path = maxDistV;
//              }
//          }
//
//          maxDistV->known = true;
//          v = maxDistV;
//      }
    }

    void printNetworkStream(int minStream)
    {
        //输出网络流
        cout << vertexs[0]->name << "->" << vertexs[vertexs.size() - 1]->name << endl;
        string path;
        Vertex* p = vertexs[vertexs.size() - 1];
        while (p)
        {
            if (!path.empty())
            {
                path = p->name + "->" + path;
            }
            else
            {
                path = p->name;
            }
            p = p->path;
        }
        cout << path << ": " << minStream << endl;
    }

private:
    vector<Vertex*> vertexs;

};

void initGraphForTopoSort(vector<Vertex*>& vertexs)
{
    //图9-4
    Vertex* v1 = new Vertex("v1", 0);
    Vertex* v2 = new Vertex("v2", 1);
    Vertex* v3 = new Vertex("v3", 2);
    Vertex* v4 = new Vertex("v4", 3);
    Vertex* v5 = new Vertex("v5", 1);
    Vertex* v6 = new Vertex("v6", 3);
    Vertex* v7 = new Vertex("v7", 2);

    vertexs.push_back(v1);
    vertexs[0]->insertAdj(v2);
    vertexs[0]->insertAdj(v4);
    vertexs[0]->insertAdj(v3);

    vertexs.push_back(v2);
    vertexs[1]->insertAdj(v4);
    vertexs[1]->insertAdj(v5);

    vertexs.push_back(v3);
    vertexs[2]->insertAdj(v6);
    
    vertexs.push_back(v4);
    vertexs[3]->insertAdj(v6);
    vertexs[3]->insertAdj(v7);
    vertexs[3]->insertAdj(v3);

    vertexs.push_back(v5);
    vertexs[4]->insertAdj(v4);
    vertexs[4]->insertAdj(v7);

    vertexs.push_back(v6);

    vertexs.push_back(v7);
    vertexs[6]->insertAdj(v6);
}

void initGraphForPath(vector<Vertex*>& vertexs)
{
    //图9-10
    Vertex* v1 = new Vertex("v1", 1);
    Vertex* v2 = new Vertex("v2", 1);
    Vertex* v3 = new Vertex("v3", 1);
    Vertex* v4 = new Vertex("v4", 2);
    Vertex* v5 = new Vertex("v5", 2);
    Vertex* v6 = new Vertex("v6", 3);
    Vertex* v7 = new Vertex("v7", 2);

    vertexs.push_back(v1);
    vertexs[0]->insertAdj(v2);
    vertexs[0]->insertAdj(v4);

    vertexs.push_back(v2);
    vertexs[1]->insertAdj(v4);
    vertexs[1]->insertAdj(v5);

    vertexs.push_back(v3);
    vertexs[2]->insertAdj(v1);
    vertexs[2]->insertAdj(v6);
    
    vertexs.push_back(v4);
    vertexs[3]->insertAdj(v6);
    vertexs[3]->insertAdj(v7);

    vertexs.push_back(v5);
    vertexs[4]->insertAdj(v7);

    vertexs.push_back(v6);

    vertexs.push_back(v7);
    vertexs[6]->insertAdj(v6);
}

void initGraphForDijkstra(vector<Vertex*>& vertexs)
{
    //图9-20
    Vertex* v1 = new Vertex("v1", 1);
    Vertex* v2 = new Vertex("v2", 1);
    Vertex* v3 = new Vertex("v3", 1);
    Vertex* v4 = new Vertex("v4", 2);
    Vertex* v5 = new Vertex("v5", 2);
    Vertex* v6 = new Vertex("v6", 3);
    Vertex* v7 = new Vertex("v7", 2);

    VertexWeighted tmp;

    vertexs.push_back(v1);
    tmp.vertex = v2;
    tmp.weight = 2;
    vertexs[0]->insertWeightedAdj(tmp);
    tmp.vertex = v4;
    tmp.weight = 1;
    vertexs[0]->insertWeightedAdj(tmp);

    vertexs.push_back(v2);
    tmp.vertex = v4;
    tmp.weight = 3;
    vertexs[1]->insertWeightedAdj(tmp);
    tmp.vertex = v5;
    tmp.weight = 10;
    vertexs[1]->insertWeightedAdj(tmp);

    vertexs.push_back(v3);
    tmp.vertex = v1;
    tmp.weight = 4;
    vertexs[2]->insertWeightedAdj(tmp);
    tmp.vertex = v6;
    tmp.weight = 5;
    vertexs[2]->insertWeightedAdj(tmp);
    
    vertexs.push_back(v4);
    tmp.vertex = v3;
    tmp.weight = 2;
    vertexs[3]->insertWeightedAdj(tmp);
    tmp.vertex = v5;
    tmp.weight = 2;
    vertexs[3]->insertWeightedAdj(tmp);
    tmp.vertex = v6;
    tmp.weight = 8;
    vertexs[3]->insertWeightedAdj(tmp);
    tmp.vertex = v7;
    tmp.weight = 4;
    vertexs[3]->insertWeightedAdj(tmp);
    
    vertexs.push_back(v5);
    tmp.vertex = v7;
    tmp.weight = 6;
    vertexs[4]->insertWeightedAdj(tmp);

    vertexs.push_back(v6);

    vertexs.push_back(v7);
    tmp.vertex = v6;
    tmp.weight = 1;
    vertexs[6]->insertWeightedAdj(tmp);
}

void initGraphForWeightedNegative(vector<Vertex*>& vertexs)
{
    //图9-20，其中把v2->v4的权修改为-3
    Vertex* v1 = new Vertex("v1", 1);
    Vertex* v2 = new Vertex("v2", 1);
    Vertex* v3 = new Vertex("v3", 1);
    Vertex* v4 = new Vertex("v4", 2);
    Vertex* v5 = new Vertex("v5", 2);
    Vertex* v6 = new Vertex("v6", 3);
    Vertex* v7 = new Vertex("v7", 2);

    VertexWeighted tmp;

    vertexs.push_back(v1);
    tmp.vertex = v2;
    tmp.weight = 2;
    vertexs[0]->insertWeightedAdj(tmp);
    tmp.vertex = v4;
    tmp.weight = 1;
    vertexs[0]->insertWeightedAdj(tmp);

    vertexs.push_back(v2);
    tmp.vertex = v4;
    tmp.weight = -3;
    vertexs[1]->insertWeightedAdj(tmp);
    tmp.vertex = v5;
    tmp.weight = 10;
    vertexs[1]->insertWeightedAdj(tmp);

    vertexs.push_back(v3);
    tmp.vertex = v1;
    tmp.weight = 4;
    vertexs[2]->insertWeightedAdj(tmp);
    tmp.vertex = v6;
    tmp.weight = 5;
    vertexs[2]->insertWeightedAdj(tmp);
    
    vertexs.push_back(v4);
    tmp.vertex = v3;
    tmp.weight = 2;
    vertexs[3]->insertWeightedAdj(tmp);
    tmp.vertex = v5;
    tmp.weight = 2;
    vertexs[3]->insertWeightedAdj(tmp);
    tmp.vertex = v6;
    tmp.weight = 8;
    vertexs[3]->insertWeightedAdj(tmp);
    tmp.vertex = v7;
    tmp.weight = 4;
    vertexs[3]->insertWeightedAdj(tmp);
    
    vertexs.push_back(v5);
    tmp.vertex = v7;
    tmp.weight = 6;
    vertexs[4]->insertWeightedAdj(tmp);

    vertexs.push_back(v6);

    vertexs.push_back(v7);
    tmp.vertex = v6;
    tmp.weight = 1;
    vertexs[6]->insertWeightedAdj(tmp);
}

void initGraphForCriticalPath(vector<Vertex*>& vertexs)
{
    //图9-34
    Vertex* v1 = new Vertex("v1", 0);
    Vertex* v2 = new Vertex("v2", 1);
    Vertex* v3 = new Vertex("v3", 1);
    Vertex* v4 = new Vertex("v4", 1);
    Vertex* v5 = new Vertex("v5", 1);
    Vertex* v6 = new Vertex("v6", 2);
    Vertex* v7 = new Vertex("v7", 2);
    Vertex* v8 = new Vertex("v8", 2);
    Vertex* v9 = new Vertex("v9", 1);
    Vertex* v10 = new Vertex("v10", 3);

    VertexWeighted tmp;

    vertexs.push_back(v1);
    tmp.vertex = v2;
    tmp.weight = 3;
    vertexs[0]->insertWeightedAdj(tmp);
    tmp.vertex = v3;
    tmp.weight = 2;
    vertexs[0]->insertWeightedAdj(tmp);

    vertexs.push_back(v2);
    tmp.vertex = v4;
    tmp.weight = 3;
    vertexs[1]->insertWeightedAdj(tmp);
    tmp.vertex = v6;
    tmp.weight = 2;
    vertexs[1]->insertWeightedAdj(tmp);

    vertexs.push_back(v3);
    tmp.vertex = v5;
    tmp.weight = 1;
    vertexs[2]->insertWeightedAdj(tmp);
    tmp.vertex = v6;
    tmp.weight = 2;
    vertexs[2]->insertWeightedAdj(tmp);
    
    vertexs.push_back(v4);
    tmp.vertex = v7;
    tmp.weight = 3;
    vertexs[3]->insertWeightedAdj(tmp);
    
    vertexs.push_back(v5);
    tmp.vertex = v8;
    tmp.weight = 2;
    vertexs[4]->insertWeightedAdj(tmp);
    tmp.vertex = v9;
    tmp.weight = 4;
    vertexs[4]->insertWeightedAdj(tmp);

    vertexs.push_back(v6);
    tmp.vertex = v7;
    tmp.weight = 3;
    vertexs[5]->insertWeightedAdj(tmp);
    tmp.vertex = v8;
    tmp.weight = 2;
    vertexs[5]->insertWeightedAdj(tmp);

    vertexs.push_back(v7);
    tmp.vertex = v10;
    tmp.weight = 1;
    vertexs[6]->insertWeightedAdj(tmp);

    vertexs.push_back(v8);
    tmp.vertex = v10;
    tmp.weight = 1;
    vertexs[7]->insertWeightedAdj(tmp);

    vertexs.push_back(v9);
    tmp.vertex = v10;
    tmp.weight = 1;
    vertexs[8]->insertWeightedAdj(tmp);

    vertexs.push_back(v10);
}

void initGraphForNetworkStream(vector<Vertex*>& vertexs)
{
    //图9-39
    Vertex* s = new Vertex("s", 0);
    Vertex* a = new Vertex("a", 1);
    Vertex* b = new Vertex("b", 2);
    Vertex* c = new Vertex("c", 1);
    Vertex* d = new Vertex("d", 2);
    Vertex* t = new Vertex("t", 2);

    VertexWeighted tmp;

    vertexs.push_back(s);
    tmp.vertex = a;
    tmp.weight = 3;
    vertexs[0]->insertWeightedAdj(tmp);
    tmp.vertex = b;
    tmp.weight = 2;
    vertexs[0]->insertWeightedAdj(tmp);

    vertexs.push_back(a);
    tmp.vertex = b;
    tmp.weight = 1;
    vertexs[1]->insertWeightedAdj(tmp);
    tmp.vertex = c;
    tmp.weight = 3;
    vertexs[1]->insertWeightedAdj(tmp);
    tmp.vertex = d;
    tmp.weight = 4;
    vertexs[1]->insertWeightedAdj(tmp);

    vertexs.push_back(b);
    tmp.vertex = d;
    tmp.weight = 2;
    vertexs[2]->insertWeightedAdj(tmp);
    
    vertexs.push_back(c);
    tmp.vertex = t;
    tmp.weight = 2;
    vertexs[3]->insertWeightedAdj(tmp);
    
    vertexs.push_back(d);
    tmp.vertex = t;
    tmp.weight = 3;
    vertexs[4]->insertWeightedAdj(tmp);

    vertexs.push_back(t);
}


int main()
{
    vector<Vertex*> vertexs;
    initGraphForTopoSort(vertexs);
    Graph g(vertexs);
    g.topoSort();
    cout << endl;

    vector<Vertex*> vertexs2;
    initGraphForTopoSort(vertexs2);
    Graph g2(vertexs2);
    g2.topoSort2();
    cout << endl;

    vector<Vertex*> vertexs3;
    initGraphForPath(vertexs3);
    Graph g3(vertexs3);
    g3.unweighted(3);
    g3.printPath();
    cout << endl;

    vector<Vertex*> vertexs4;
    initGraphForPath(vertexs4);
    Graph g4(vertexs4);
    g4.unweighted2(3);
    g4.printPath();
    cout << endl;

    vector<Vertex*> vertexs5;
    initGraphForPath(vertexs5);
    Graph g5(vertexs5);
    g5.unweighted3(3);
    g5.printPath();
    cout << endl;

    vector<Vertex*> vertexs6;
    initGraphForDijkstra(vertexs6);
    Graph g6(vertexs6);
    g6.dijkstra(1);
    g6.printPath();
    cout << endl;

    vector<Vertex*> vertexs7;
    initGraphForWeightedNegative(vertexs7);
    Graph g7(vertexs7);
    g7.weightedNegative(1);
    g7.printPath();
    cout << endl;

    vector<Vertex*> vertexs8;
    initGraphForCriticalPath(vertexs8);
    Graph g8(vertexs8);
    g8.criticalPath(1);
    g8.printPath();
    g8.printCriticalPath();
    cout << endl;

//  vector<Vertex*> vertexs9;
//  initGraphForNetworkStream(vertexs9);
//  Graph g9(vertexs9);
//  g9.networkStream();
//  g9.printPath();
//  cout << endl;

    return 0;
}

