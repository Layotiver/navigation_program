#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <fstream>
using namespace std;

#define MAXV 25000010
#define MAXE 100000010

int s, t;
int dis[MAXV], pre[MAXV], hd[MAXV], pos[MAXV];
int e_cnt;
int list[MAXV];
bool in[MAXV];

struct Edge
{
    int to, l, nt;
} e[MAXE];

//增加一条由a指向b长度为c的边
inline void AddEdge(int a, int b, int c)
{
    e_cnt++;
    e[e_cnt].to = b;
    e[e_cnt].l = c;
    e[e_cnt].nt = hd[a];
    hd[a] = e_cnt;
    return;
}

//输出路径长度和路径
inline void Print()
{
    printf("%d\n", dis[t]);
    for (int p = t; p != s; p = pre[p])
    {
        printf("%d <- ", p);
    }
    printf("%d\n", s);
    return;
}

//朴素dijkstra
inline void dijkstra()
{
    int i, a, b;
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    list[++list[0]] = s;
    while (list[0])
    {
        b = 0x3fffffff;
        for (i = 1; i <= list[0]; i++)
        {
            if (b > dis[list[i]])
            {
                b = dis[list[i]];
                a = i;
            }
        }
        b=list[a];
        for(i=a;i<list[0];i++)
        {
            list[i]=list[i+1];
        }
        a=b;
        list[0]--;
        if (a == t)
        {
            Print();
            return;
        }

        in[a] = 0;
        b = hd[a];
        while (b)
        {
            if (dis[e[b].to] > dis[a] + e[b].l)
            {
                pre[e[b].to] = a;
                dis[e[b].to] = dis[a] + e[b].l;
                if (!in[e[b].to])
                {
                    list[++list[0]] = e[b].to;
                    in[e[b].to] = 1;
                }
            }
            b = e[b].nt;
        }
    }
    return;
}

//输入数据和建图
void build()
{
    ifstream fin("disPro.bit", ios::binary);
    int i, n, a, b, now = 1;
    while (!fin.eof())
    {
        fin.read((char *)&n, 4);
        for (i = 1; i <= n; i++)
        {
            fin.read((char *)&a, 4);
            fin.read((char *)&b, 4);
            AddEdge(now, a, b);
            //printf("%d %d %d\n",now,a,b);
        }
        now++;
    }
    fin.close();
    return;
}

int main()
{
    build();
    freopen("chenhao.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> s >> t;
    dijkstra();
    return 0;
}