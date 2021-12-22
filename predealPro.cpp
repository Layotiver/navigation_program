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
using namespace std;
#define MAXV 25000010
#define MAXE 100000010

int s, t;
int hd[MAXV], cnt[MAXV], maxx;
int e_cnt;

char buffer[1 << 20], *p1, *p2;

struct Edge
{
    int to, l, nt;
} e[MAXE];

inline char gc()
{
    return p1 == p2 && (p2 = (p1 = buffer) + fread(buffer, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

inline void re(int &a)
{
    char c;
    while (!isdigit(c = gc()))
    {
        if (c == EOF)
        {
            a = EOF;
            return;
        }
    }
    a = c - '0';
    while (isdigit(c = gc()))
        a = a * 10 + c - '0';
    return;
}

//增加一条由a指向b长度为c的边
inline void AddEdge(int a, int b, int c)
{
    cnt[a]++;
    e_cnt++;
    e[e_cnt].to = b;
    e[e_cnt].l = c;
    e[e_cnt].nt = hd[a];
    hd[a] = e_cnt;
    return;
}

inline void Print()
{
    int i, b;
    for (i = 1; i <= maxx; i++)
    {
        fwrite(&cnt[i], sizeof(int), 1, stdout);
        b = hd[i];
        while (b)
        {
            fwrite(&e[b].to, sizeof(int), 1, stdout);
            fwrite(&e[b].l, sizeof(int), 1, stdout);
            b = e[b].nt;
        }
    }
    return;
}

int main()
{
    freopen("distance_info.txt", "r", stdin);
    freopen("disPro.bit", "wb", stdout);
    int a, b, c;
    while (1)
    {
        re(a);
        if (a == -1)
            break;
        maxx = maxx > a ? maxx : a;
        re(b);
        maxx = maxx > b ? maxx : b;
        re(c);
        AddEdge(a, b, c);
    }
    Print();
    return 0;
}