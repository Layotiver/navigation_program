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
int heap[MAXV]; //heap[0]存储堆内元素个数

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

//将节点a压入堆内
inline void push(int a)
{
    int b = ++heap[0];
    heap[b] = a;
    pos[a] = heap[0];
    while (dis[b] < dis[b >> 1] && b > 1)
    {
        pos[heap[b]] = b >> 1;
        pos[heap[b >> 1]] = b;
        heap[b] ^= heap[b >> 1] ^= heap[b] ^= heap[b >> 1];
    }
    return;
}

//向上调整
void AdjustUp(int a)
{
    if (a > 1 && dis[a] < dis[a >> 1])
    {
        pos[heap[a]] = a >> 1;
        pos[heap[a >> 1]] = a;
        heap[a] ^= heap[a >> 1] ^= heap[a] ^= heap[a >> 1];
        AdjustUp(a >> 1);
    }
    return;
}

//向下调整
void AdjustDown(int a)
{
    if ((dis[a] < dis[a << 1] || (a << 1) > heap[0]) && (dis[a] < dis[a << 1 | 1] || (a << 1 | 1) > heap[0]))
        return;
    if (dis[a] > dis[a << 1] && (a << 1) <= heap[0])
    {
        if (dis[a] > dis[a << 1 | 1] && (a << 1 | 1) <= heap[0])
        {
            if (dis[a << 1] < dis[a << 1 | 1])
            {
                pos[heap[a]] = a << 1;
                pos[heap[a << 1]] = a;
                heap[a] ^= heap[a << 1] ^= heap[a] ^= heap[a << 1];
                AdjustDown(a << 1);
            }
            else
            {
                pos[heap[a]] = a << 1 | 1;
                pos[heap[a << 1 | 1]] = a;
                heap[a] ^= heap[a << 1 | 1] ^= heap[a] ^= heap[a << 1 | 1];
                AdjustDown(a << 1 | 1);
            }
        }
        else
        {
            pos[heap[a]] = a << 1;
            pos[heap[a << 1]] = a;
            heap[a] ^= heap[a << 1] ^= heap[a] ^= heap[a << 1];
            AdjustDown(a << 1);
        }
    }
    else
    {
        pos[heap[a]] = a << 1 | 1;
        pos[heap[a << 1 | 1]] = a;
        heap[a] ^= heap[a << 1 | 1] ^= heap[a] ^= heap[a << 1 | 1];
        AdjustDown(a << 1 | 1);
    }
    return;
}

//删除堆顶元素
inline void pop()
{
    pos[heap[1]] = 0;
    heap[1] = heap[heap[0]];
    pos[heap[1]] = 1;
    heap[0]--;
    AdjustDown(1);
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

//堆优化的dijkstra
inline void dijkstra()
{
    int i, a, b;
    for (i = 1; i <= 25000000; i++)
    {
        dis[i] = 0x3fffffff;
    }
    dis[s] = 0;
    push(s);
    while (heap[0])
    {
        a = heap[1];
        if (a == t)
        {
            Print();
            return;
        }
        pop();

        b = hd[a];
        while (b)
        {
            if (dis[e[b].to] > dis[a] + e[b].l)
            {
                pre[e[b].to] = a;
                dis[e[b].to] = dis[a] + e[b].l;
                if (pos[e[b].to])
                {
                    AdjustUp(pos[e[b].to]);
                }
                else
                {
                    push(e[b].to);
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